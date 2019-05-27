#ifndef ECS_UNIT_SYSTEM_H
#define ECS_UNIT_SYSTEM_H

#define VILLAGER_MODEL 0
#define CHICKEN_MODEL  1

#include "ecs/entities/entityManager.hpp"

class UnitSystem
{
public:
    static void init();
    static void update();
    static void destroy();

    static EntityManager<Unit>& getUnits();

private:
    static EntityManager<Unit> units;
};

#endif // ECS_UNIT_SYSTEM_H
