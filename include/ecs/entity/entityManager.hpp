#ifndef ECS_ENTITY_MANAGER_H
#define ECS_ENTITY_MANAGER_H

#include "ecs/entity/entity.hpp"

class EntityManagerLogger
{
public:
    inline static void increaseCreatedGlobalEntitiesCounter() { ++createdGlobalEntitiesCount; }
    inline static void increaseDestroyedGlobalEntitiesCounter() { ++destroyedGlobalEntitiesCount; }

    static void outLog();

private:
    explicit EntityManagerLogger() {}

    static uint32 createdGlobalEntitiesCount;
    static uint32 destroyedGlobalEntitiesCount;
};

template <typename E>
class EntityManager
{
public:
    explicit EntityManager() {}
    virtual ~EntityManager();

    E* createEntity();
    bool removeEntity(E* entity);
    void clear();

    inline List<Entity*>& getEntities() { return this->entities; }

private:
    uint32 currentID = 0;
    List<Entity*> entities;
};

#endif // ECS_ENTITY_MANAGER_H
