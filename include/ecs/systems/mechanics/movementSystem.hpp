#ifndef ECS_MOVEMENT_SYSTEM_H
#define ECS_MOVEMENT_SYSTEM_H

#include "ecs/entities/entityManager.hpp"
#include "ecs/systems/unit/unitSystem.hpp"

class MovementSystem
{
public:
    static void init();
    static void update(float deltaTime);
    static void destroy();
};

#endif // ECS_MOVEMENT_SYSTEM_H
