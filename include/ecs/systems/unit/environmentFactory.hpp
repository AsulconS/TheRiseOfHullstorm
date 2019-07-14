#ifndef ECS_ENVIRONMENT_FACTOTY_H
#define ECS_ENVIRONMENT_FACTOTY_H

#include "ecs/systems/unit/abstractFactory.hpp"

#include "ecs/entity/entities.hpp"

class EnvironmentFactory : public AbstractFactory
{
public:
    static void forge(Destructible* instance, const DestructibleType destructible);

private:
    static void forgeTree01(Destructible* instance);
    static void forgeTree02(Destructible* instance);
    static void forgeTree03(Destructible* instance);
    static void forgeMine(Destructible* instance);
};

#endif // ECS_ENVIRONMENT_FACTOTY_H
