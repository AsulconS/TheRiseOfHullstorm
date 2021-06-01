#define  ECS_IMPLEMENTATION
#include "ecs.hpp"

int main()
{
    // Component Manager is Implicitly Initialized
    UnitSystem::init();
    MovementSystem::init();

    RenderingSystem::init(AUTO_SIZE, true);
    InputSystem::init();

    MapSystem::init();
    PlayerSystem::init();

    MapSystem::loadMap(5);

    float deltaTime = 0.0f;
    while(RenderingSystem::isActive())
    {
        deltaTime = getDeltaTime();

        // Process Input
        InputSystem::update(deltaTime);
        UnitSystem::update(deltaTime);
        PlayerSystem::update(deltaTime);

        // Then Trigger Systems
        MovementSystem::update(deltaTime);

        // Finally Render the results
        RenderingSystem::update(deltaTime);
        MapSystem::update(deltaTime);
    }

    RenderingSystem::destroy();
    InputSystem::destroy();
    MovementSystem::destroy();
    PlayerSystem::destroy();
    UnitSystem::destroy();
    MapSystem::destroy();

    ComponentManager::outLog();
    EntityManagerLogger::outLog();

    return 0;
}
