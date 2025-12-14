#pragma once

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
