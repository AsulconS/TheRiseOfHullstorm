#ifndef ECS_OXIMORPH_FACTOTY_H
#define ECS_OXIMORPH_FACTOTY_H

#include "ecs/entities/entity.hpp"
#include "ecs/systems/unit/abstractFactory.hpp"

class OximorphFactory : public AbstractFactory
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
    static void forgeArchery(Building* instance);
    static void forgeFarm(Building* instance);
};

#endif // ECS_OXIMORPH_FACTORY_H
