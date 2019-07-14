#ifndef ECS_UNIT_SYSTEM_H
#define ECS_UNIT_SYSTEM_H

#include "ecs/entity/entityManager.hpp"
#include "ecs/entity/entities.hpp"

#include "ecs/systems/unit/abstractFactory.hpp"

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
    static void createBuilding(const uint32 player, const BuildingType building, const glm::vec3& pos, const glm::vec3& rot = glm::vec3(0.0f, 0.0f, 0.0f), const glm::vec3& sca = glm::vec3(1.0f, 1.0f, 1.0f));
    template <typename Factory>
    static void createDestructible(const DestructibleType destructible, const glm::vec3& pos, const glm::vec3& rot = glm::vec3(0.0f, 0.0f, 0.0f), const glm::vec3& sca = glm::vec3(1.0f, 1.0f, 1.0f));

    static inline EntityManager<Unit>& getUnits(const uint32 player) { return units[player]; }
    static inline EntityManager<Building>& getBuildings(const uint32 player) { return buildings[player]; }
    static inline EntityManager<Destructible>& getDestructibles() { return destructibles; }

private:
    explicit UnitSystem() {}

    static Vector<EntityManager<Unit>> units;
    static Vector<EntityManager<Building>> buildings;
    static EntityManager<Destructible> destructibles;
    static uint32 index;
};

#endif // ECS_UNIT_SYSTEM_H
