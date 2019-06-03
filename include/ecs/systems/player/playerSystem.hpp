#ifndef ECS_PLAYER_SYSTEM_H
#define ECS_PLAYER_SYSTEM_H

#include "ecs/component/componentManager.hpp"
#include "ecs/entities/entityManager.hpp"

class PlayerSystem
{
public:
    static void init();
    static void update(float deltaTime);
    static void destroy();

    static void createVillager(const glm::vec3& pos);
    static void createChicken(const glm::vec3& pos);

    static Unit* dummy;
};

#endif // ECS_PLAYER_SYSTEM_H