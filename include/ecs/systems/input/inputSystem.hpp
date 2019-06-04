#ifndef ECS_INPUT_SYSTEM_H
#define ECS_INPUT_SYSTEM_H

#include <GLFW/glfw3.h>

#include "system/common.hpp"
#include "ecs/systems/rendering/renderingSystem.hpp"
#include "ecs/systems/player/playerSystem.hpp"

class InputSystem
{
public:
    static void init();
    static void update(float deltaTime);
    static void destroy();

private:
    static GLFWwindow* window;
    static uint32 screenshotCount;

    static double mouseXPos;
    static double mouseYPos;
    static bool isInBorder;
    static bool isClicking;
    
    static uint32 currentDummyModel;

    static void scrollCallback(GLFWwindow* _window, double xOffset, double yOffset);
};

#endif // ECS_INPUT_SYSTEM_H
