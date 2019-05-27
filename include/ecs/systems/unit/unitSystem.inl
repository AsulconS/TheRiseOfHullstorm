EntityManager<Unit> UnitSystem::units;

void UnitSystem::init()
{
    Unit* chicken = units.createEntity();
    chicken->meshRenderer->index = CHICKEN_MODEL;
    chicken->stats->velocity = 0.0025f;

    Unit* villager = units.createEntity();
    villager->meshRenderer->index = VILLAGER_MODEL;;
    
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
