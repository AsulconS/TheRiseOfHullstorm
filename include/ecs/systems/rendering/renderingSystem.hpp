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
    static void init(uint32 width = 800, uint32 height = 600, uint32 glVersion = 3);
    static void update(float deltaTime);
    static void destroy();

    static bool isActive();
    static void stop();

    static glm::vec3 from2DPosition(const glm::vec2& pos);
    static glm::vec3 rayCast(const glm::vec2& pos);

    // ------------------------------------------------------------------------------

    static GLFWwindow* window;
    static Camera* mainCamera;

private:
    static Shader shader;
    static Shader hudShader;

    // HUD Properties
    // --------------
    static uint32 HVAO;
    static uint32 HVBO;
    static uint32 HEBO;
    static uint32 hudTexture;
    static Vector<float> hudVertices;
    static Vector<uint32> hudIndices;

    // Loaded Models
    static Vector<Model*> models;

    // Window Properties
    // -----------------
    static uint32 windowWidth;
    static uint32 windowHeight;

    // Camera Properties
    // -----------------
    static glm::mat4 projection;
    static glm::mat4 view;
    static glm::vec3 cameraFront;

    // Rendering Functions
    // -------------------
    static void renderHud();

    // Setup Functions
    // ---------------------------------------------------------------------
    static void initDisplay(uint32 width, uint32 height, uint32 glVersion);
    static void loadHudVertices();
    static void setupCamera();
    static void setupLights();
    static void centerWindow();

    static void framebufferSizeCallback(GLFWwindow* _window, int32 width, int32 height);
};

#endif // ESC_RENDERING_SYSTEM_H
