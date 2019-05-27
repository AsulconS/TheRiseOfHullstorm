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
        //unit->getTransform()->position.x += unit->getStats()->velocity;
        //unit->getTransform()->position.y += unit->getStats()->velocity;
        unit->getTransform()->position.z += unit->getStats()->velocity;
    }
}

void MovementSystem::destroy()
{
    //
}
