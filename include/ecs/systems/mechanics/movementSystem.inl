void MovementSystem::init()
{
    //
}

void MovementSystem::update(float deltaTime)
{
    Unit* unit;
    List<BaseComponent*>& transformMemory = ComponentManager::getComponentMemory<Transform>();
    List<BaseComponent*>::iterator i;
    List<BaseComponent*>::iterator j;
    
    for(i = transformMemory.begin(); i != transformMemory.end(); ++i)
    {
        if((*i)->entity->type != UNIT_ENTITY)
            continue;
        
        unit = (Unit*)((*i)->entity);
        if(unit->transform->isStatic)
            continue;
        if(unit->transform->position == unit->transform->target)
            continue;
        
        move(unit, deltaTime);

        // Check Collisions
        // ----------------------------------------------------------------
        Unit* other;
        for(j = transformMemory.begin(); j != transformMemory.end(); ++j)
        {
            if((*j)->entity->type != UNIT_ENTITY)
                continue;
            
            other = (Unit*)((*j)->entity);
            if(other == unit)
                continue;

            checkColisions(unit, other, deltaTime);
        }
        // ----------------------------------------------------------------
    }
}

void MovementSystem::destroy()
{
    std::cout << "Movement System Destroyed" << std::endl;
}

void MovementSystem::move(Unit* unit, float deltaTime)
{
    glm::vec3 directionVector(unit->transform->target - unit->transform->position);
    unit->transform->position += glm::normalize(directionVector) * unit->stats->velocity * deltaTime;
}

void MovementSystem::checkColisions(Unit* unit, Unit* other, float deltaTime)
{
    glm::vec3 directionVector(other->transform->position - unit->transform->position);
    float distance = glm::length(directionVector);

    if(distance <= (unit->circleCollider->radius + other->circleCollider->radius))
        unit->transform->position -= glm::normalize(directionVector) * unit->stats->velocity * deltaTime;
}
