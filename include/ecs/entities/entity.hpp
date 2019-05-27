#ifndef ECS_ENTITY_H
#define ECS_ENTITY_H

#include <iostream>

#include "system/common.hpp"
#include "dataStructures.hpp"

#include "ecs/component/componentManager.hpp"

class Entity
{
public:
    virtual void init(uint32 _ID) = 0;
    virtual void destroy() = 0;
    virtual void print() = 0;
    uint32 ID;

    Transform* transform;

protected:
    void internalInit(uint32 _ID);
};

class EmptyEntity : public Entity
{
public:
    virtual void init(uint32 _ID);
    virtual void destroy();
    virtual void print();
};

class Unit : public Entity
{
public:
    virtual void init(uint32 _ID);
    virtual void destroy();
    virtual void print();

    MeshRenderer* meshRenderer;
    Stats* stats;
};

#endif // ECS_ENTITY_H
