#ifndef ECS_COMPONENT_H
#define ECS_COMPONENT_H

#include <glm/glm.hpp>

#include "system/common.hpp"

class Entity;

struct BaseComponent
{
    Entity* entity;
};

template <typename T>
struct Component : public BaseComponent
{
    static const uint32 ID;
    static const uint32 SIZE;
};

struct Transform : public Component<Transform>
{
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    glm::vec3 target;

    bool isStatic;
};

struct MeshRenderer : public Component<MeshRenderer>
{
    uint32 index;

    float alpha;
    bool isVisible;
};

struct CameraComponent : public Component<CameraComponent>
{
    bool mainCamera;
    bool perspective;
    
    float fov;
    float cNear;
    float cFar;
};

// Colliders
// -----------------------------------------------------------

struct BoxCollider2D : public Component<BoxCollider2D>
{
    glm::vec3 size;

    bool isSolid;
    bool isTrigger;
};

struct BoxCollider : public Component<BoxCollider>
{
    glm::vec3 center;
    glm::vec3 size;

    bool isSolid;
    bool isTrigger;
};

struct CircleCollider2D : public Component<CircleCollider2D>
{
    float radius;

    bool isSolid;
    bool isTrigger;
};

// -----------------------------------------------------------

struct Stats : public Component<Stats>
{
    float hp;
    float damage;
    float defense;
    float velocity;
};

#endif // ECS_COMPONENT_H
