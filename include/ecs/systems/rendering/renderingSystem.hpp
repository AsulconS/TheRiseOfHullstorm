#ifndef ECS_RENDERING_SYSTEM_H
#define ECS_RENDERING_SYSTEM_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <cmath>

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

    static glm::vec3 from2DPosition(const glm::vec2& pos);
    static glm::vec3 rayCast(const glm::vec2& pos);

    static Camera* mainCamera;
    static glm::mat4 projection;
    static glm::mat4 view;
    static glm::vec3 cameraFront;
    
    static uint32 windowWidth;
    static uint32 windowHeight;
    static GLFWwindow* getContextWindow();

private:
    static GLFWwindow* window;
    static Shader shader;

    static Vector<Model*> models;

    static void initDisplay(uint32 glVersion);
    static void setupCamera();
    static void setupLights();
    static void centerWindow();

    static void framebufferSizeCallback(GLFWwindow* _window, int32 width, int32 height);
};

#endif // ESC_RENDERING_SYSTEM_H
