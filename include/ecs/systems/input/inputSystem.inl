// Static Initializations
// ----------------------------------------

GLFWwindow* InputSystem::window = NULL;
bool InputSystem::isClicking = false;
uint32 InputSystem::currentDummy = -1;

// ----------------------------------------

void InputSystem::init()
{
    window = RenderingSystem::window;
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    glfwSetScrollCallback(window, scrollCallback);
}

void InputSystem::update(float deltaTime)
{
    // Camera Movement
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        RenderingSystem::stop();
    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        RenderingSystem::mainCamera->transform->position.z -= 64.0f * deltaTime;
    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        RenderingSystem::mainCamera->transform->position.z += 64.0f * deltaTime;
    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        RenderingSystem::mainCamera->transform->position.x += 64.0f * deltaTime;
    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        RenderingSystem::mainCamera->transform->position.x -= 64.0f * deltaTime;
    
    // Dummy Creator
    if(glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
        currentDummy = VILLAGER_MODEL;
    if(glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
        currentDummy = CHICKEN_MODEL;
    if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        currentDummy = -1;
    
    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !isClicking)
    {
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        float xPos = (float)x;
        float yPos = (float)y;

        glm::vec3 pos = RenderingSystem::from2DPosition(glm::vec2(xPos, yPos));

        switch (currentDummy)
        {
            case VILLAGER_MODEL:
                PlayerSystem::createVillager(pos);
                break;
            
            case CHICKEN_MODEL:
                PlayerSystem::createChicken(pos);
                break;

            default:
                break;
        }

        isClicking = true;
    }
    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
        isClicking = false;
    
    if(currentDummy != -1)
    {
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        float xPos = (float)x;
        float yPos = (float)y;

        PlayerSystem::dummy->transform->position = RenderingSystem::from2DPosition(glm::vec2(xPos, yPos));
        PlayerSystem::dummy->meshRenderer->index = currentDummy;
        PlayerSystem::dummy->meshRenderer->isVisible = true;
    }
    else
        PlayerSystem::dummy->meshRenderer->isVisible = false;
    
    glfwPollEvents();
}

void InputSystem::destroy()
{
    std::cout << "Input system Destroyed" << std::endl;
}

void InputSystem::scrollCallback(GLFWwindow* _window, double xOffset, double yOffset)
{
    float& fov = RenderingSystem::mainCamera->cameraComponent->fov;
    if(fov >= 44.3f && fov <= 45.0f)
        fov -= (float)yOffset / 32.0f;
    
    if(fov <= 44.3f)
        fov = 44.3f;
    if(fov >= 45.0f)
        fov = 45.0f;
}
