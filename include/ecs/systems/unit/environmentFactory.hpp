#ifndef ECS_ENVIRONMENT_FACTOTY_H
#define ECS_ENVIRONMENT_FACTOTY_H

#include "ecs/component/componentManager.hpp"
#include "ecs/systems/unit/abstractFactory.hpp"

class EnvironmentFactory : public AbstractFactory
{
public:
    static void forge(Unit* instance, const UnitType unit);

private:
    static void forgeTree01(Unit* instance);
    static void forgeTree02(Unit* instance);
    static void forgeTree03(Unit* instance);
    static void forgeMine(Unit* instance);
};

#endif // ECS_ENVIRONMENT_FACTOTY_H
