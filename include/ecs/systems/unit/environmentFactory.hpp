#ifndef ECS_ENVIRONMENT_FACTOTY_H
#define ECS_ENVIRONMENT_FACTOTY_H

#include "ecs/component/componentManager.hpp"
#include "ecs/systems/unit/abstractFactory.hpp"

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
