void EnvironmentFactory::forge(Unit* instance, const UnitType unit)
{
    switch(unit)
    {
        case TREE01:
            forgeTree01(instance);
            break;
        case TREE02:
            forgeTree02(instance);
            break;
        default:
            forgeUnknown(instance);
            break;
    }
}

void EnvironmentFactory::forgeTree01(Unit* instance)
{
    instance->meshRenderer->index = TREE01;
    instance->stats->velocity = 0.0f;
}

void EnvironmentFactory::forgeTree02(Unit* instance)
{
    instance->meshRenderer->index = TREE02;
    instance->stats->velocity = 0.0f;
}
