#ifndef ECS_MOVEMENT_SYSTEM_H
#define ECS_MOVEMENT_SYSTEM_H

#include "ecs/systems/unit/unitSystem.hpp"

class MovementSystem
{
public:
    static void init();
    static void update(float deltaTime);
    static void destroy();

    static bool isBetween(glm::vec3 pos, glm::vec3 origin, glm::vec3 boundings);

private:
    explicit MovementSystem() {}

    static void moveTowardsTarget(Unit* unit, float deltaTime);
    static void checkColisions(CircleCollider2D* source, CircleCollider2D* other, float outer, float deltaTime);
    static void checkColisions(CircleCollider2D* source, BoxCollider2D* other, float outer, float deltaTime);
};

#endif // ECS_MOVEMENT_SYSTEM_H
