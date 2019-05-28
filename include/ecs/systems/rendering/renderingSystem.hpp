#ifndef ECS_RENDERING_SYSTEM_H
#define ECS_RENDERING_SYSTEM_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "system/common.hpp"
#include "dataStructures.hpp"
#include "ecs/component/componentManager.hpp"
#include "ecs/entities/entityManager.hpp"
#include "ecs/systems/rendering/shader.hpp"

class RenderingSystem
{
public:
    static void init();
    static void update(float deltaTime);
    static void destroy();

    static bool isActive();
    static void stop();

    static GLFWwindow* getContextWindow();

private:
    static GLFWwindow* window;
    static Camera* mainCamera;
    static Shader shader;

    static Vector<Model*> models;

    static void initDisplay(uint32 glVersion);

    static void framebufferSizeCallback(GLFWwindow* _window, int32 width, int32 height);
};

#endif // ESC_RENDERING_SYSTEM_H
