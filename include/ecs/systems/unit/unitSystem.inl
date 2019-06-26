Vector<EntityManager<Unit>> UnitSystem::units;
Vector<EntityManager<Building>> UnitSystem::buildings;
EntityManager<Destructible> UnitSystem::destructibles;
uint32 UnitSystem::index = 0;

void UnitSystem::init()
{
    //
}

template <typename Factory>
void UnitSystem::createUnit(const uint32 player, const UnitType unit, const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& sca)
{
    static_assert(std::is_base_of<AbstractFactory, Factory>::value, "This must be a Factory!");
    
    Unit* instance = units[player].createEntity();
    instance->transform->position = pos;
    instance->transform->rotation = rot;
    instance->transform->scale    = { 4.0f, 4.0f, 4.0f };

    instance->transform->target = pos;
    
    // Factory of The Race
    Factory::forge(instance, unit);
}

template <typename Factory>
void UnitSystem::createBuilding(const uint32 player, const BuildingType building, const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& sca)
{
    static_assert(std::is_base_of<AbstractFactory, Factory>::value, "This must be a Factory!");
    
    Building* instance = buildings[player].createEntity();
    instance->transform->position = pos;
    instance->transform->rotation = rot;
    instance->transform->scale    = { 4.0f, 4.0f, 4.0f };

    instance->transform->target = pos;
    
    // Factory of The Race
    Factory::forge(instance, building);
}

template <typename Factory>
void UnitSystem::createDestructible(const DestructibleType destructible, const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& sca)
{
    static_assert(std::is_base_of<AbstractFactory, Factory>::value, "This must be a Factory!");
    
    Destructible* instance = destructibles.createEntity();
    instance->transform->position = pos;
    instance->transform->rotation = rot;
    instance->transform->scale    = { 4.0f, 4.0f, 4.0f };

    instance->transform->target = pos;
    
    // Factory of The Race
    Factory::forge(instance, destructible);
}

uint32 UnitSystem::registerPlayer()
{
    units.push_back(EntityManager<Unit>());
    buildings.push_back(EntityManager<Building>());
    return index++;
}

void UnitSystem::clear()
{
    for(size_t i = 0; i < units.size(); ++i)
        units[i].clear();
    for(size_t i = 0; i < buildings.size(); ++i)
        buildings[i].clear();
    destructibles.clear();
}

void UnitSystem::update(float deltaTime)
{
    //
}

void UnitSystem::destroy()
{
    clear();
    units.clear();
    buildings.clear();
    std::cout << "Unit System Destroyed" << std::endl;
}
