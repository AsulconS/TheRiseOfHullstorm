#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <chrono>

#define  ECS_IMPLEMENTATION
#define  STB_IMAGE_IMPLEMENTATION
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
    UnitSystem::init();
    MovementSystem::init();

    RenderingSystem::init();
    InputSystem::init();

    PlayerSystem::init();

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
    }

    RenderingSystem::destroy();
    InputSystem::destroy();
    MovementSystem::destroy();
    PlayerSystem::destroy();

    return 0;
}
