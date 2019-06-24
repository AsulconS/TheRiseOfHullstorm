void MovementSystem::init()
{
    //
}

void MovementSystem::update(float deltaTime)
{
    Unit* unit;
    List<BaseComponent*>& memory = ComponentManager::getComponentMemory<Transform>();
    List<BaseComponent*>::iterator i;
    
    for(i = memory.begin(); i != memory.end(); ++i)
    {
        if((*i)->entity->type != UNIT_ENTITY)
            continue;
        
        unit = (Unit*)((*i)->entity);
        if(unit->transform->position == unit->transform->targetPoint)
            continue;
        
        move(unit, deltaTime);
    }
}

void MovementSystem::destroy()
{
    std::cout << "Movement System Destroyed" << std::endl;
}

void MovementSystem::move(Unit* unit, float deltaTime)
{
    if(unit->transform->isStatic) return;

    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;

    glm::vec3 objective = unit->transform->targetPoint;
    moveTowards(unit, objective, up, down, left, right);
    checkObstacles(unit, objective, up, down, left, right, deltaTime);
    if(up)
        moveUp(unit, objective, deltaTime);
    if(down)
        moveDown(unit, objective, deltaTime);
    if(left)
        moveLeft(unit, objective, deltaTime);
    if(right)
        moveRight(unit, objective, deltaTime);
}

void MovementSystem::moveTowards(Unit* unit, glm::vec3 objective, bool& up, bool& down, bool& left, bool& right)
{
    left = false;
    right = false;
    up = false;
    down = false;

    if(unit->transform->position.x > objective.x)
        left = true;
    else if(unit->transform->position.x < objective.x)
        right = true;
    if(unit->transform->position.z > objective.z)
        up = true;
    else if(unit->transform->position.z < objective.z)
        down = true;
}

void MovementSystem::moveUp(Unit* unit, glm::vec3 objective, float deltaTime)
{
    float speed = unit->stats->velocity * deltaTime;
    float balancedspeed = (getYdis(unit, objective) / getDistance(unit, objective)) * speed;
    if(balancedspeed < getYdis(unit, objective))
        unit->transform->position.z -= balancedspeed;
    else
        unit->transform->position.z = objective.z;
}

void MovementSystem::moveDown(Unit* unit, glm::vec3 objective, float deltaTime)
{
    float speed = unit->stats->velocity * deltaTime;
    float balancedspeed = getYdis(unit, objective) / getDistance(unit, objective) * speed;
    if(balancedspeed < getYdis(unit, objective))
        unit->transform->position.z += balancedspeed;
    else
        unit->transform->position.z = objective.z;
}
void MovementSystem::moveRight(Unit* unit, glm::vec3 objective, float deltaTime)
{
    float speed = unit->stats->velocity * deltaTime;
    float balancedspeed = getXdis(unit, objective) / getDistance(unit,objective) * speed;
    if(balancedspeed < getXdis(unit, objective))
        unit->transform->position.x += balancedspeed;
    else
        unit->transform->position.x = objective.x;
}

void MovementSystem::moveLeft(Unit* unit,glm::vec3 objective,float deltaTime)
{
    float speed = unit->stats->velocity * deltaTime;
    float balancedspeed = getXdis(unit, objective) / getDistance(unit, objective) * speed;
    if(balancedspeed < getXdis(unit, objective))
        unit->transform->position.x -= balancedspeed;
    else
        unit->transform->position.x = objective.x;
}

float MovementSystem::getXdis(Unit* unit, glm::vec3 objective)
{
    return abs(unit->transform->position.x - objective.x);
}

float MovementSystem::getYdis(Unit* unit, glm::vec3 objective)
{
    return abs(unit->transform->position.z - objective.z);
}

float MovementSystem::getDistance(Unit* unit,glm::vec3 objective)
{
    float xdis = getXdis(unit, objective);
    float ydis = getYdis(unit, objective);
    return sqrt(pow(xdis, 2) + pow(ydis, 2));
}

void MovementSystem::setExtremes(Unit* unit, float& up, float& down, float& left, float& right)
{
    glm::vec3 size = unit->boxCollider->size;
    glm::vec3 position = unit->transform->position;

    up = position.z - size.z / 2.0f;
    down = position.z + size.z / 2.0f;
    left = position.x - size.x / 2.0f;
    right = position.x + size.x / 2.0f;

}

bool MovementSystem::between(float val, float left, float right)
{
    return val > left && val < right;
}



void MovementSystem::checkColisions(Unit* unit, Unit* unit2, bool& up, bool& down, bool& left, bool& right, float deltaTime)
{
    glm::vec3 objetive = unit->transform->targetPoint;
    glm::vec3 position = unit->transform->position;
    float up2, down2, left2, right2;

    float speed = unit->stats->velocity * deltaTime;
    float speedX = getXdis(unit, objetive) / getDistance(unit, objetive) * speed;
    float speedY = getYdis(unit, objetive) / getDistance(unit, objetive) * speed;
    setExtremes(unit2, up2, down2, left2, right2);
    if(between(position.x, left2, right2) && position.z - speedY < down2 && position.z - speedY > up2)
        up = false;
    
    if(between(position.x, left2, right2) && between(position.z + speedY, up2, down2))
        down = false;
    
    if(between(position.z, up2, down2) && position.x - speedX < right2 && position.x - speedX > left2)
        left = false;
    
    if(between(position.z, up2, down2) && between(position.x + speedX, left2, right2))
        right = false;
}

void MovementSystem::checkObstacles(Unit* unit, glm::vec3& objective, bool& up, bool& down, bool& left, bool& right, float deltaTime)
{
    Unit* unit2;
    List<BaseComponent*>& memory = ComponentManager::getComponentMemory<Transform>();
    List<BaseComponent*>::iterator i;
    for(i = memory.begin(); i != memory.end(); ++i)
    {
        if((*i)->entity->type != UNIT_ENTITY)
            continue;
        unit2 = (Unit*)((*i)->entity);
        if(unit == unit2)
            continue;
        
        checkColisions(unit, unit2, up, down, left, right, deltaTime);
    }
}
