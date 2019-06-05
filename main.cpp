#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cstdio>
#include <chrono>

#define  ECS_IMPLEMENTATION
#define  STB_IMAGE_IMPLEMENTATION
#define  STB_IMAGE_WRITE_IMPLEMENTATION
#include "ecs.hpp"

static auto currentTime = std::chrono::steady_clock::now();
static auto lastTime = currentTime;
static auto timeSpan = std::chrono::duration_cast<std::chrono::duration<float>>(currentTime - lastTime);

static float deltaTime = 0.0f;

float getDeltaTime()
{
    currentTime = std::chrono::steady_clock::now();
    timeSpan = std::chrono::duration_cast<std::chrono::duration<float>>(currentTime - lastTime);
    lastTime = currentTime;
    return timeSpan.count();
}

int main()
{
    // Component Manager is Implicitly Initialized
    UnitSystem::init();
    MovementSystem::init();

    RenderingSystem::init();
    InputSystem::init();

    PlayerSystem::init();
    MapSystem::init();

    MapSystem::loadMap(2);
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
    std::cout << globalEntitiesCount << " entities created!" << std::endl;
    std::cout << destroyedGlobalEntitiesCount << " entities destroyed!" << std::endl;

    return 0;
}
