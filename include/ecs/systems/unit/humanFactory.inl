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
    instance->meshRenderer->index = CHICKEN;
    instance->stats->velocity = 10.0f;
}

void HumanFactory::forgeCastle(Building* instance)
{
    instance->meshRenderer->index = CASTLE;
}

void HumanFactory::forgeBarracks(Building* instance)
{
    instance->meshRenderer->index = BARRACKS;
}
