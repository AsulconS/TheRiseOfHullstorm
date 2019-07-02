void HumanFactory::forge(Unit* instance, const UnitType unit)
{
    switch(unit)
    {
        case CHICKEN:
            forgeChicken(instance);
            break;
        case VILLAGER:
            forgeVillager(instance);
            break;
        case SOLDIER:
            forgeSoldier(instance);
            break;
        case BOWMAN:
            forgeBowman(instance);
            break;
        default:
            forgeUnknown(instance);
            break;
    }
}

void HumanFactory::forge(Building* instance, const BuildingType building)
{
    switch(building)
    {
        case CASTLE:
            forgeCastle(instance);
            break;
        case BARRACKS:
            forgeBarracks(instance);
            break;
        case ARCHERY:
            forgeArchery(instance);
            break;
        case FARM:
            forgeFarm(instance);
            break;
        default:
            forgeUnknown(instance);
            break;
    }
}

void HumanFactory::forgeVillager(Unit* instance)
{
    instance->meshRenderer->index = VILLAGER;
    instance->stats->velocity = 10.0f;
}

void HumanFactory::forgeSoldier(Unit* instance)
{
    instance->meshRenderer->index = SOLDIER;
    instance->stats->velocity = 10.0f;
}

void HumanFactory::forgeBowman(Unit* instance)
{
    instance->meshRenderer->index = BOWMAN;
    instance->stats->velocity = 10.0f;
}

void HumanFactory::forgeChicken(Unit* instance)
{
    instance->transform->scale = { 1.0f, 1.0f, 1.0f };
    instance->meshRenderer->index = CHICKEN;
    instance->stats->velocity = 10.0f;
}

void HumanFactory::forgeCastle(Building* instance)
{
    instance->meshRenderer->index = CASTLE;
    instance->boxCollider->size = { 3.0f, 0.0f, 3.0f };
    instance->unitType = VILLAGER;
}

void HumanFactory::forgeBarracks(Building* instance)
{
    instance->meshRenderer->index = BARRACKS;
    instance->boxCollider->size = { 2.0f, 0.0f, 2.0f };
    instance->unitType = SOLDIER;
}

void HumanFactory::forgeArchery(Building* instance)
{
    instance->meshRenderer->index = ARCHERY;
    instance->boxCollider->size = { 2.0f, 0.0f, 2.0f };
    instance->unitType = BOWMAN;
}

void HumanFactory::forgeFarm(Building* instance)
{
    instance->meshRenderer->index = FARM;
    instance->boxCollider->size = { 2.0f, 0.0f, 2.0f };
    instance->unitType = CHICKEN;
}
