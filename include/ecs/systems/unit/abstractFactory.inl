void AbstractFactory::forgeUnknown(Unit* instance)
{
    instance->meshRenderer->index = UNKNOWN;
    instance->stats->velocity = 10.0f;
}

void AbstractFactory::forgeUnknown(Building* instance)
{
    instance->meshRenderer->index = UNKNOWN;
    instance->stats->velocity = 0.0f;
}

void AbstractFactory::forgeUnknown(Destructible* instance)
{
    instance->meshRenderer->index = UNKNOWN;
}
