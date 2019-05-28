#ifndef ECS_INPUT_SYSTEM_H
#define ECS_INPUT_SYSTEM_H

#include <GLFW/glfw3.h>

#include "system/common.hpp"
#include "ecs/systems/rendering/renderingSystem.hpp"

class InputSystem
{
public:
    static void init();
    static void update(float deltaTime);
    static void destroy();

private:
    static GLFWwindow* window;
};

#endif // ECS_INPUT_SYSTEM_H
