#ifndef ECS_COMPONENT_H
#define ECS_COMPONENT_H

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

#endif // ECS_COMPONENT_H
