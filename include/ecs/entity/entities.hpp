#ifndef ECS_ENTITIES_H
#define ECS_ENTITIES_H

#include "ecs/component/components.hpp"

#include "ecs/entity/entity.hpp"
#include "ecs/entity/entityManager.hpp"

class EmptyEntity : public Entity
{
public:
    virtual void init(uint32 _id) override;
    virtual void destroy() override;
};

class Player : public Entity
{
public:
    virtual void init(uint32 _id) override;
    virtual void destroy() override;

    PlayerData* playerData;
};

class Camera : public Entity
{
public:
    virtual void init(uint32 _id) override;
    virtual void destroy() override;

    CameraComponent* cameraComponent;
};

class Unit : public Entity
{
public:
    virtual void init(uint32 _id) override;
    virtual void destroy() override;

    MeshRenderer* meshRenderer;
    CircleCollider2D* circleCollider;
    Stats* stats;
};

class Building : public Entity
{
public:
    virtual void init(uint32 _id) override;
    virtual void destroy() override;

    MeshRenderer* meshRenderer;
    BoxCollider2D* boxCollider;
    Stats* stats;
    UnitType unitType;
};

class Destructible : public Entity
{
public:
    virtual void init(uint32 _id) override;
    virtual void destroy() override;

    MeshRenderer* meshRenderer;
    CircleCollider2D* circleCollider;
};

#endif // ECS_ENTITIES_H
