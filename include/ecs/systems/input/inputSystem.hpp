#pragma once

#include <GLFW/glfw3.h>
#include <filesystem>
#include <format>

#include "ecs/systems/player/playerSystem.hpp"
#include "ecs/systems/rendering/renderingSystem.hpp"

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
	explicit InputSystem() {}

	static GLFWwindow* window;
	static uint32 screenshotCount;

	// Mouse Properties
	// ----------------
	static double mouseXPos;
	static double mouseYPos;
	static double lastMouseXPos;
	static double lastMouseYPos;
	static double virtualXPos;
	static double virtualYPos;
	// -----------------
	static bool isClicking;
	static bool isSaving;
	
	static uint32 currentDummy;

	static void mouseBoundingsCalculation(float deltaTime);

	template <typename T>
	static T loadValueFromFile(const String& filename);
	template <typename T>
	static void saveValueToFile(const T& value, const String& filename);

	static void scrollCallback(GLFWwindow* _window, double xOffset, double yOffset);
};
