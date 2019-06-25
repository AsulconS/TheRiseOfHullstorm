#ifndef ECS_ABSTRACT_FACTOTY_H
#define ECS_ABSTRACT_FACTOTY_H

#include "ecs/component/componentManager.hpp"

class AbstractFactory
{
protected:
    static void forgeUnknown(Unit* instance);
    static void forgeUnknown(Building* instance);

private:
    explicit AbstractFactory() {}
};

#endif // ECS_ABSTRACT_FACTOTY_H