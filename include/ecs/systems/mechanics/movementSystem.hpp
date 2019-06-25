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

private:
    explicit MovementSystem() {}

    static void move(Unit* unit, float deltaTime);
    static void checkColisions(Unit* unit, Unit* other, float deltaTime);
};

#endif // ECS_MOVEMENT_SYSTEM_H
