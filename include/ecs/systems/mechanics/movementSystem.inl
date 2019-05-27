void MovementSystem::init()
{
    //
}

void MovementSystem::update()
{
    std::cout << "----------------" << std::endl;
    std::cout << "MOVEMENT SYSTEM:" << std::endl;
    std::cout << "----------------" << std::endl;

    Unit* unit;
    List<BaseComponent*>& memory = ComponentManager::getComponentMemory<Transform>();
    List<BaseComponent*>::iterator i;
    for(i = memory.begin(); i != memory.end(); ++i)
    {
        unit = (Unit*)((*i)->entity);
        //unit->transform->position.x += unit->stats->velocity;
        //unit->transform->position.y += unit->stats->velocity;
        unit->transform->position.z += unit->stats->velocity;
    }
}

void MovementSystem::destroy()
{
    //
}
