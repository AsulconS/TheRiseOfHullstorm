#ifndef ECS_UNIT_SYSTEM_H
#define ECS_UNIT_SYSTEM_H

#include "ecs/entities/entityManager.hpp"

class UnitSystem
{
public:
    static void init();
    static void update(float deltaTime);
    static void destroy();

    static void createVillager(const glm::vec3& pos);
    static void createChicken(const glm::vec3& pos);

    static EntityManager<Unit>& getUnits();

private:
    static EntityManager<Unit> units;
};

#endif // ECS_UNIT_SYSTEM_H
