#ifndef ECS_PLAYER_SYSTEM_H
#define ECS_PLAYER_SYSTEM_H

#include "ecs/component/componentManager.hpp"
#include "ecs/entities/entityManager.hpp"

/* Input System:
 * --------------
 * Entities: 1
 * Components: 3
 * -------------- */
class PlayerSystem
{
public:
    static void init();
    static void update(float deltaTime);
    static void destroy();

    static void createUnit(const UnitType unit, const glm::vec3& pos);
    static void createBuilding(const BuildingType building, const glm::vec3& pos);

    static Unit* dummy;

private:
    explicit PlayerSystem() {}
    
    static uint32 playerInstance;
};

#endif // ECS_PLAYER_SYSTEM_H
