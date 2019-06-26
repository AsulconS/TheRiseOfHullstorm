void EnvironmentFactory::forge(Destructible* instance, const DestructibleType destructible)
{
    switch(destructible)
    {
        case TREE01:
            forgeTree01(instance);
            break;
        case TREE02:
            forgeTree02(instance);
            break;
        case TREE03:
            forgeTree03(instance);
            break;
        case MINE:
            forgeMine(instance);
            break;
        default:
            forgeUnknown(instance);
            break;
    }
}

void EnvironmentFactory::forgeTree01(Destructible* instance)
{
    instance->transform->isStatic = true;
    instance->meshRenderer->index = TREE01;
}

void EnvironmentFactory::forgeTree02(Destructible* instance)
{
    instance->transform->isStatic = true;
    instance->meshRenderer->index = TREE02;
}

void EnvironmentFactory::forgeTree03(Destructible* instance)
{
    instance->transform->isStatic = true;
    instance->meshRenderer->index = TREE03;
}

void EnvironmentFactory::forgeMine(Destructible* instance)
{
    instance->transform->isStatic = true;
    instance->meshRenderer->index = MINE;
}
