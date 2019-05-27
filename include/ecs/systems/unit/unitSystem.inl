EntityManager<Unit> UnitSystem::units;

void UnitSystem::init()
{
    for(size_t i = 0; i < 1; ++i)
        units.createEntity();
    
    units.printEntities();
}

void UnitSystem::update()
{
    units.printEntities();
}

void UnitSystem::destroy()
{
    units.clear();
}

EntityManager<Unit>& UnitSystem::getUnits()
{
    return units;
}
