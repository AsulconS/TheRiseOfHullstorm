#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define  ECS_IMPLEMENTATION
#define  STB_IMAGE_IMPLEMENTATION
#include "ecs.hpp"

int main()
{
    UnitSystem::init();

    RenderingSystem::init();
    InputSystem::init();

    MovementSystem::init();

    while(RenderingSystem::isActive())
    {
        // Process Input
        InputSystem::update();
        UnitSystem::update();

        // Then Trigger Systems
        MovementSystem::update();

        // Finally Render the results
        RenderingSystem::update();
    }

    RenderingSystem::destroy();
    InputSystem::destroy();
    MovementSystem::destroy();

    return 0;
}
