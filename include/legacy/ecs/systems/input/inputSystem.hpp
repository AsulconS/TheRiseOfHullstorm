#ifndef ECS_INPUT_SYSTEM_H
#define ECS_INPUT_SYSTEM_H

#include <GLFW/glfw3.h>

#include "system/common.hpp"
#include "ecs/systems/rendering/renderingSystem.hpp"
#include "ecs/systems/player/playerSystem.hpp"

/* Input System:
 * --------------
 * Entities: 0
 * Components: 0
 * -------------- */
class InputSystem
{
public:
    static void init();
    static void update(float deltaTime);
    static void destroy();

private:
    static GLFWwindow* window;
    static uint32 screenshotCount;

    // Mouse Properties
    // ----------------
    static double mouseXPos;
    static double mouseYPos;
    static bool isInBorder;
    static bool isClicking;
    static bool isSaving;
    // -----------------
    
    static uint32 currentDummyModel;

    template <typename T>
    static T loadValueFromFile(const String& filename);
    template <typename T>
    static void saveValueToFile(const T& value, const String& filename);

    static void scrollCallback(GLFWwindow* _window, double xOffset, double yOffset);
};

#endif // ECS_INPUT_SYSTEM_H
