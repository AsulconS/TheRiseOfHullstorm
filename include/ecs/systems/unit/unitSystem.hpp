#ifndef ECS_UNIT_SYSTEM_H
#define ECS_UNIT_SYSTEM_H

#include "ecs/entities/entityManager.hpp"

class UnitSystem
{
public:
    static void init();
    static void update(float deltaTime);
    static void destroy();

    static void clear();

    static void createVillager(const glm::vec3& pos, const glm::vec3& rot = glm::vec3(0.0f, 0.0f, 0.0f), const glm::vec3& sca = glm::vec3(1.0f, 1.0f, 1.0f));
    static void createChicken(const glm::vec3& pos, const glm::vec3& rot = glm::vec3(0.0f, 0.0f, 0.0f), const glm::vec3& sca = glm::vec3(1.0f, 1.0f, 1.0f));
    
    static void spawnTree(const glm::vec3& pos, const glm::vec3& rot = glm::vec3(0.0f, 0.0f, 0.0f), const glm::vec3& sca = glm::vec3(1.0f, 1.0f, 1.0f));

    static EntityManager<Unit>& getUnits();

private:
    static EntityManager<Unit> units;
};

#endif // ECS_UNIT_SYSTEM_H
