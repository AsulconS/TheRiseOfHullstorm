#ifndef ECS_ENTITY_H
#define ECS_ENTITY_H

#include <iostream>

#include "system/common.hpp"
#include "dataStructures.hpp"

#include "ecs/component/componentManager.hpp"

class Entity
{
public:
    virtual void init(uint32 _id) = 0;
    virtual void destroy() = 0;
    virtual void print() = 0;

    uint32 id;
    uint32 type;
    Transform* transform;

protected:
    void internalInit(uint32 _id, uint32 _type);
};

class EmptyEntity : public Entity
{
public:
    virtual void init(uint32 _id);
    virtual void destroy();
    virtual void print();
};

class Camera : public Entity
{
public:
    virtual void init(uint32 _id);
    virtual void destroy();
    virtual void print();

    CameraComponent* cameraComponent;
};

class Unit : public Entity
{
public:
    virtual void init(uint32 _id);
    virtual void destroy();
    virtual void print();

    MeshRenderer* meshRenderer;
    Stats* stats;
};

#endif // ECS_ENTITY_H
