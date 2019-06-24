#ifndef ECS_UNIT_SYSTEM_H
#define ECS_UNIT_SYSTEM_H

#include "ecs/entities/entityManager.hpp"

/* Unit System:
 * ---------------
 * Entities: n
 * Components: 3n
 * --------------- */
class UnitSystem
{
public:
    static void init();
    static void update(float deltaTime);
    static void destroy();

    static void clear();

    static uint32 registerPlayer();

    template <typename Factory>
    static void createUnit(const uint32 player, const UnitType unit, const glm::vec3& pos, const glm::vec3& rot = glm::vec3(0.0f, 0.0f, 0.0f), const glm::vec3& sca = glm::vec3(1.0f, 1.0f, 1.0f));
    template <typename Factory>
    static void createBuilding(const uint32 player, const UnitType unit, const glm::vec3& pos, const glm::vec3& rot = glm::vec3(0.0f, 0.0f, 0.0f), const glm::vec3& sca = glm::vec3(1.0f, 1.0f, 1.0f));

    static EntityManager<Unit>& getUnits(const uint32 player);
    static EntityManager<Building>& getBuildings(const uint32 player);

private:
    explicit UnitSystem() {}

    static Vector<EntityManager<Unit>> units;
    static Vector<EntityManager<Building>> buildings;
    static uint32 index;
};

#endif // ECS_UNIT_SYSTEM_H
