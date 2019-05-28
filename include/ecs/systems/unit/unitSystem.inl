EntityManager<Unit> UnitSystem::units;
//string unidad
void UnitSystem::init()
{
    Unit* unit;

    for(size_t i = 0; i < 5; ++i)
    {
        unit = units.createEntity();

        unit->transform->position.x = 0.5f * i - 1.0f;
        unit->transform->position.z = 0.5f;

        unit->transform->rotation.y = 64.0f * i;

        unit->transform->scale = { 0.1f, 0.1f, 0.1f };

        unit->meshRenderer->index = CHICKEN_MODEL;

        unit->stats->velocity = 0.0002f;
    }
    for(size_t i = 0; i < 5; ++i)
    {
        unit = units.createEntity();

        unit->transform->position.x = 1.25f * i - 2.25f;
        unit->transform->position.z = -1.0f;

        unit->transform->rotation.y = 64.0f * i;

        unit->meshRenderer->index = VILLAGER_MODEL;

        unit->stats->velocity = 0.0002f;
    }
    for(size_t i = 0; i < 5; ++i)
    {
        unit = units.createEntity();

        unit->transform->position.x = 2.5f * i - 5.0f;
        unit->transform->position.z = -4.0f;
        unit->transform->scale = { 0.4f, 0.4f, 0.4f };


        unit->transform->rotation.y = 64.0f * i;

        unit->meshRenderer->index = TREE_MODEL;

        unit->stats->velocity = 0.0002f;
    }

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
