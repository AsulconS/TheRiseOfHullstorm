void OximorphFactory::forge(Unit* instance, const UnitType unit)
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

void OximorphFactory::forge(Building* instance, const BuildingType building)
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

void OximorphFactory::forgeVillager(Unit* instance)
{
    instance->meshRenderer->index = VILLAGER;
    instance->stats->velocity = 20.0f;
}

void OximorphFactory::forgeSoldier(Unit* instance)
{
    instance->meshRenderer->index = SOLDIER;
    instance->stats->velocity = 20.0f;
}

void OximorphFactory::forgeBowman(Unit* instance)
{
    instance->meshRenderer->index = BOWMAN;
    instance->stats->velocity = 20.0f;
}

void OximorphFactory::forgeChicken(Unit* instance)
{
    instance->meshRenderer->index = CHICKEN;
    instance->stats->velocity = 20.0f;
}

void OximorphFactory::forgeCastle(Building* instance)
{
    instance->meshRenderer->index = CASTLE;
}

void OximorphFactory::forgeBarracks(Building* instance)
{
    instance->meshRenderer->index = BARRACKS;
}

void OximorphFactory::forgeArchery(Building* instance)
{
    instance->meshRenderer->index = ARCHERY;
}

void OximorphFactory::forgeFarm(Building* instance)
{
    instance->meshRenderer->index = FARM;
}
