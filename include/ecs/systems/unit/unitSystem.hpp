#ifndef ECS_UNIT_SYSTEM_H
#define ECS_UNIT_SYSTEM_H

#include "ecs/entities/entityManager.hpp"

class UnitSystem
{
public:
    static void init();
    static void update();
    static void destroy();

    static void createVillager();

    static EntityManager<Unit>& getUnits();

private:
    static EntityManager<Unit> units;
};

#endif // ECS_UNIT_SYSTEM_H
