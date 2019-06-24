#ifndef ECS_HUMAN_FACTOTY_H
#define ECS_HUMAN_FACTOTY_H

#include "ecs/component/componentManager.hpp"
#include "ecs/systems/unit/abstractFactory.hpp"

class HumanFactory : public AbstractFactory
{
public:
    static void forge(Unit* instance, const UnitType unit);
    static void forge(Building* instance, const BuildingType building);

private:
    static void forgeVillager(Unit* instance);
    static void forgeSoldier(Unit* instance);
    static void forgeBowman(Unit* instance);
    static void forgeChicken(Unit* instance);

    static void forgeCastle(Building* instance);
    static void forgeBarracks(Building* instance);
};

#endif // ECS_HUMAN_FACTOTY_H
