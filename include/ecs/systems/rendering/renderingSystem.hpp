#ifndef ECS_RENDERING_SYSTEM_H
#define ECS_RENDERING_SYSTEM_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <cmath>

#include "system/stb_image.h"
#include "system/stb_image_write.h"
#include "system/common.hpp"
#include "dataStructures.hpp"
#include "ecs/component/componentManager.hpp"
#include "ecs/entities/entityManager.hpp"
#include "ecs/systems/rendering/shader.hpp"
#include "ecs/systems/rendering/model.hpp"
#include "ecs/systems/rendering/sprite.hpp"

/* Rendering System:
 * ------------------
 * Entities: 1
 * Components: 2
 * ------------------ */
class RenderingSystem
{
public:
    static void init(uint32 width = 1280, uint32 height = 720, bool fullScreen = false, uint32 glVersion = 3);
    static void update(float deltaTime);
    static void destroy();

    static bool isActive();
    static void stop();

    static glm::vec3 from2DPosition(const glm::vec2& pos);
    static glm::vec3 rayCast(const glm::vec2& pos);

    // Utils
    // -----
    static uint32 loadTextureFromFile(const char* filename, const String& directory, bool isFlipped);
    static void saveScreenshot(const String& filename);

    // Main Camera
    // -----------
    static Camera* mainCamera;
    static Sprite cursor;

    // Window Properties
    // -----------------
    static GLFWwindow* window;
    static uint32 windowWidth;
    static uint32 windowHeight;

private:
    static Shader shader;
    static Shader hudShader;

    // HUD Properties
    // --------------
    static Sprite hud;

    // Loaded Models
    static Vector<Model*> models;

    // Camera Properties
    // -----------------
    static glm::mat4 projection;
    static glm::mat4 view;
    static glm::vec3 cameraFront;

    // Setup Functions
    // ---------------------------------------------------------------------
    static void initDisplay(uint32 width, uint32 height, bool fullScreen, uint32 glVersion);
    static void setupCamera();
    static void setupLights();
    static void centerWindow();

    static void framebufferSizeCallback(GLFWwindow* _window, int32 width, int32 height);
};

#endif // ESC_RENDERING_SYSTEM_H
