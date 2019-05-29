float MovementSystem::scaleFactor = 0.0f;

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
        //unit->transform->position.x += unit->stats->velocity;
        //unit->transform->position.y += unit->stats->velocity;
        unit->transform->position.z += unit->stats->velocity * deltaTime;
        unit->transform->rotation.y = sin(scaleFactor * deltaTime) * 8.0f;
        scaleFactor += 1.0f;
    }
}

void MovementSystem::destroy()
{
    //
}
