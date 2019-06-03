EntityManager<Unit> UnitSystem::units;

void UnitSystem::init()
{
    Unit* unit;

    // VILLAGERS
    for(size_t i = 0; i < 5; ++i)
    {
        unit = units.createEntity();

        unit->transform->position.x = 8.0f * i - 16.0f;
        unit->transform->position.z = -2.0f;

        unit->transform->rotation.y = 64.0f * i;

        unit->meshRenderer->index = VILLAGER_MODEL;

        unit->stats->velocity = 10.0f;
    }

    // CHICKENS
    for(size_t i = 0; i < 5; ++i)
    {
        unit = units.createEntity();

        unit->transform->position.x = 4.0f * i - 8.0f;
        unit->transform->position.z = 8.0f;

        unit->transform->rotation.y = 64.0f * i;

        unit->meshRenderer->index = CHICKEN_MODEL;

        unit->stats->velocity = 10.0f;
    }

    // TREES
    for(size_t i = 0; i < 5; ++i)
    {
        unit = units.createEntity();

        unit->transform->position.x = 16.0f * i - 32.0f;
        unit->transform->position.z = -14.0f;

        unit->transform->rotation.y = 64.0f * i;

        unit->transform->scale = { 2.5f, 2.5f, 2.5f };

        unit->meshRenderer->index = TREE_MODEL;

        unit->stats->velocity = 10.0f;
    }
}

void UnitSystem::createVillager(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& sca)
{
    Unit* unit = units.createEntity();

    unit->transform->position = pos;
    unit->transform->rotation = rot;
    unit->transform->scale    = sca;

    unit->meshRenderer->index = VILLAGER_MODEL;

    unit->stats->velocity = 10.0f;
}

void UnitSystem::createChicken(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& sca)
{
    Unit* unit = units.createEntity();

    unit->transform->position = pos;
    unit->transform->rotation = rot;
    unit->transform->scale    = sca;

    unit->meshRenderer->index = CHICKEN_MODEL;

    unit->stats->velocity = 10.0f;
}

void UnitSystem::spawnTree(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& sca)
{
    Unit* unit = units.createEntity();

    unit->transform->position = pos;
    unit->transform->rotation = rot;
    unit->transform->scale    = sca;

    unit->meshRenderer->index = TREE_MODEL;

    unit->stats->velocity = 10.0f;
}

void UnitSystem::clear()
{
    units.clear();
}

void UnitSystem::update(float deltaTime)
{
    //
}

void UnitSystem::destroy()
{
    units.clear();
}

EntityManager<Unit>& UnitSystem::getUnits()
{
    return units;
}
