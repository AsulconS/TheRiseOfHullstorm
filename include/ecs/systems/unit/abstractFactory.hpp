#ifndef ECS_ABSTRACT_FACTOTY_H
#define ECS_ABSTRACT_FACTOTY_H

#include "ecs/entity/entities.hpp"

class AbstractFactory
{
protected:
    static void forgeUnknown(Unit* instance);
    static void forgeUnknown(Building* instance);
    static void forgeUnknown(Destructible* instance);

private:
    explicit AbstractFactory() {}
};

#endif // ECS_ABSTRACT_FACTOTY_H
