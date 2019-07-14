#ifndef ECS_ENTITY_H
#define ECS_ENTITY_H

#include <iostream>

#include "ecs/component/components.hpp"

class Entity
{
public:
    virtual void init(uint32 _id) = 0;
    virtual void destroy() = 0;

    uint32 id;
    uint32 type;
    
    Transform* transform;

protected:
    void internalInit(uint32 _id, uint32 _type);
};

#endif // ECS_ENTITY_H
