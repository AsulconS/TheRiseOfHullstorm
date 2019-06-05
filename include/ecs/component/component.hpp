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

struct BoxCollider : public Component<BoxCollider>
{
    glm::vec3 center;
    glm::vec3 size;

    bool isTrigger;
};

struct Stats : public Component<Stats>
{
    float hp;
    float damage;
    float defense;
    float velocity;
};

#endif // ECS_COMPONENT_H
