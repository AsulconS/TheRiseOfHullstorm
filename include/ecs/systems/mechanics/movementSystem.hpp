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

    static bool between(float val, float left, float right);
    static void checkColisions(Unit* unit01, Unit* unit02, bool& up, bool& down, bool& left, bool& right, float deltaTime);
    static void checkObstacles(Unit* unit, glm::vec3& objective, bool& up, bool& down, bool& left, bool& right, float deltaTime);

    static void move(Unit* unit, float deltaTime);
    static void moveTowards(Unit* unit, glm::vec3 objective, bool& up, bool& down, bool& left, bool& right);
    static void moveRight(Unit* unit, glm::vec3 objective, float deltaTime);
    static void moveLeft(Unit* unit, glm::vec3 objective, float deltaTime);
    static void moveUp(Unit* unit, glm::vec3 objective, float deltaTime);
    static void moveDown(Unit* unit, glm::vec3 objective, float deltaTime);
    static void setExtremes(Unit* unit, float& up,float& down, float& left,float& right);

    static float getXdis(Unit* unit, glm::vec3 objective);
    static float getYdis(Unit* unit, glm::vec3 objective);
    static float getDistance(Unit* unit, glm::vec3 objective);

private:
    explicit MovementSystem() {}
};

#endif // ECS_MOVEMENT_SYSTEM_H
