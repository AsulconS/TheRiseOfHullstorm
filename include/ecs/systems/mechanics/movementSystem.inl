void MovementSystem::init()
{
    //
}

void MovementSystem::update(float deltaTime)
{
    Unit* unit;
    List<BaseComponent*>& transformMemory = ComponentManager::getComponentMemory<Transform>();
    List<BaseComponent*>& circleCollider2DMemory = ComponentManager::getComponentMemory<CircleCollider2D>();
    List<BaseComponent*>& boxCollider2DMemory = ComponentManager::getComponentMemory<BoxCollider2D>();
    List<BaseComponent*>::iterator i;
    List<BaseComponent*>::iterator j;
    
    for(i = transformMemory.begin(); i != transformMemory.end(); ++i)
    {
        if((*i)->entity->type != UNIT_ENTITY)
            continue;
        
        unit = (Unit*)((*i)->entity);
        if(!unit->circleCollider->isSolid && !unit->circleCollider->isTrigger)
            continue;
        if(unit->transform->isStatic)
            continue;
        if(unit->transform->position != unit->transform->target)
            moveTowardsTarget(unit, deltaTime);

        // Check Collisions
        // ----------------------------------------------------------------
        CircleCollider2D* otherCircle;
        for(j = circleCollider2DMemory.begin(); j != circleCollider2DMemory.end(); ++j)
        {   
            otherCircle = (CircleCollider2D*)(*j);
            if(otherCircle == unit->circleCollider)
                continue;
            if(!otherCircle->isSolid && !otherCircle->isTrigger)
                continue;

            checkColisions(unit->circleCollider, otherCircle, unit->stats->velocity, deltaTime);
        }
        BoxCollider2D* otherBox;
        for(j = boxCollider2DMemory.begin(); j != boxCollider2DMemory.end(); ++j)
        {   
            otherBox = (BoxCollider2D*)(*j);
            if(!otherBox->isSolid && !otherBox->isTrigger)
                continue;

            checkColisions(unit->circleCollider, otherBox, unit->stats->velocity, deltaTime);
        }
        // ----------------------------------------------------------------
    }
}

void MovementSystem::destroy()
{
    std::cout << "Movement System Destroyed" << std::endl;
}

void MovementSystem::moveTowardsTarget(Unit* unit, float deltaTime)
{
    glm::vec3 directionVector(unit->transform->target - unit->transform->position);
    unit->transform->position += glm::normalize(directionVector) * unit->stats->velocity * deltaTime;
}

void MovementSystem::checkColisions(CircleCollider2D* source, CircleCollider2D* other, float outer, float deltaTime)
{
    glm::vec3 directionVector(other->entity->transform->position - source->entity->transform->position);
    float distance = glm::length(directionVector);

    if(distance <= (source->radius + other->radius))
        source->entity->transform->position -= glm::normalize(directionVector) * outer * deltaTime;
}

void MovementSystem::checkColisions(CircleCollider2D* source, BoxCollider2D* other, float outer, float deltaTime)
{
    glm::vec3 directionVector(other->entity->transform->position - source->entity->transform->position);
    float distance = glm::length(directionVector);

    if(distance <= (source->radius + glm::length(other->size)))
        source->entity->transform->position -= glm::normalize(directionVector) * outer * deltaTime;
}

bool MovementSystem::isBetween(glm::vec3 pos, glm::vec3 origin, glm::vec3 boundings)
{
    if((pos.x < (origin.x + boundings.x)) && (pos.x > (origin.x - boundings.x))
    && (pos.z < (origin.z + boundings.z)) && (pos.z > (origin.z - boundings.z)))
        return true;
    return false;
}
