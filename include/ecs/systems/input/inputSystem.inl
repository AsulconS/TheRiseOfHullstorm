// Static Initializations
// ----------------------------------------

GLFWwindow* InputSystem::window = NULL;

double InputSystem::mouseXPos;
double InputSystem::mouseYPos;
bool InputSystem::isInBorder = false;
bool InputSystem::isClicking = false;

uint32 InputSystem::currentDummy = -1;

// ----------------------------------------

void InputSystem::init()
{
    window = RenderingSystem::window;
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    glfwSetScrollCallback(window, scrollCallback);
    
    mouseXPos = RenderingSystem::windowWidth / 2;
    mouseYPos = RenderingSystem::windowHeight / 2;
    glfwSetCursorPos(window, mouseXPos, mouseYPos);
}

void InputSystem::update(float deltaTime)
{
    glfwGetCursorPos(window, &mouseXPos, &mouseYPos);
    RenderingSystem::cursor.setPosition(glm::vec2((float)mouseXPos, (float)mouseYPos));

    if(mouseXPos <= 1)
    {
        mouseXPos = 1;
        RenderingSystem::mainCamera->transform->position.x -= 64.0f * deltaTime;
        isInBorder = true;
    }
    else if(mouseXPos >= (RenderingSystem::windowWidth - 1))
    {
        mouseXPos = RenderingSystem::windowWidth - 1;
        RenderingSystem::mainCamera->transform->position.x += 64.0f * deltaTime;
        isInBorder = true;
    }
    
    if(mouseYPos <= 1)
    {
        mouseYPos = 1;
        RenderingSystem::mainCamera->transform->position.z -= 64.0f * deltaTime;
        isInBorder = true;
    }
    else if(mouseYPos >= (RenderingSystem::windowHeight - 1))
    {
        mouseYPos = RenderingSystem::windowHeight - 1;
        RenderingSystem::mainCamera->transform->position.z += 64.0f * deltaTime;
        isInBorder = true;
    }
    
    if(isInBorder)
        glfwSetCursorPos(window, mouseXPos, mouseYPos);

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
        float xPos = (float)mouseXPos;
        float yPos = (float)mouseYPos;

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
        float xPos = (float)mouseXPos;
        float yPos = (float)mouseYPos;

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
