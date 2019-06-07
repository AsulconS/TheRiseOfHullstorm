// Static Initializations
// ----------------------------------------

GLFWwindow* InputSystem::window = NULL;
uint32 InputSystem::screenshotCount = 0;

double InputSystem::mouseXPos;
double InputSystem::mouseYPos;
bool InputSystem::isInBorder = false;
bool InputSystem::isClicking = false;
bool InputSystem::isSaving = false;

#ifdef MOUSE_FIX
    double InputSystem::virtualXPos;
    double InputSystem::virtualYPos;
    double InputSystem::lastMouseXPos;
    double InputSystem::lastMouseYPos;
#endif

uint32 InputSystem::currentDummyModel = -1;

// ----------------------------------------

void InputSystem::init()
{
    window = RenderingSystem::window;
    glfwSetScrollCallback(window, scrollCallback);

    #ifdef MOUSE_FIX
        virtualXPos = RenderingSystem::windowWidth / 2;
        virtualYPos = RenderingSystem::windowHeight / 2;
        glfwGetCursorPos(window, &mouseXPos, &mouseYPos);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        RenderingSystem::cursor.setPosition(glm::vec2((float)virtualXPos, (float)virtualYPos));
    #else
        mouseXPos = RenderingSystem::windowWidth / 2;
        mouseYPos = RenderingSystem::windowHeight / 2;

        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        glfwSetCursorPos(window, mouseXPos, mouseYPos);
    #endif

    screenshotCount = loadValueFromFile<uint32>("sc");
}

void InputSystem::update(float deltaTime)
{
    glfwGetCursorPos(window, &mouseXPos, &mouseYPos);

    #ifdef MOUSE_FIX
        virtualXPos += mouseXPos - lastMouseXPos;
        virtualYPos += mouseYPos - lastMouseYPos;
        lastMouseXPos = mouseXPos;
        lastMouseYPos = mouseYPos;
        RenderingSystem::cursor.setPosition(glm::vec2((float)virtualXPos, (float)virtualYPos));

        if(virtualXPos <= 1)
        {
            virtualXPos = 1;
            RenderingSystem::mainCamera->transform->position.x -= 64.0f * deltaTime;
        }
        else if(virtualXPos >= (RenderingSystem::windowWidth - 1))
        {
            virtualXPos = RenderingSystem::windowWidth - 1;
            RenderingSystem::mainCamera->transform->position.x += 64.0f * deltaTime;
        }
        
        if(virtualYPos <= 1)
        {
            virtualYPos = 1;
            RenderingSystem::mainCamera->transform->position.z -= 64.0f * deltaTime;
        }
        else if(virtualYPos >= (RenderingSystem::windowHeight - 1))
        {
            virtualYPos = RenderingSystem::windowHeight - 1;
            RenderingSystem::mainCamera->transform->position.z += 64.0f * deltaTime;
        }
    #else
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
    #endif

    // Camera Movement
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        RenderingSystem::stop();
    
    if(glfwGetKey(window, GLFW_KEY_F12) == GLFW_PRESS && !isSaving)
    {
        RenderingSystem::saveScreenshot("screenshots/screenshot-" + std::to_string(screenshotCount++) + ".jpg");
        isSaving = true;
    }
    if(glfwGetKey(window, GLFW_KEY_F12) == GLFW_RELEASE)
        isSaving = false;
    
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
        currentDummyModel = VILLAGER_MODEL;
    if(glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
        currentDummyModel = CHICKEN_MODEL;
    if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        currentDummyModel = -1;
    
    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !isClicking)
    {
        float xPos = (float)mouseXPos;
        float yPos = (float)mouseYPos;

        glm::vec3 pos = RenderingSystem::from2DPosition(glm::vec2(xPos, yPos));

        switch (currentDummyModel)
        {
            case VILLAGER_MODEL:
                PlayerSystem::createVillager(pos);
                std::cout << "Villager created in pos: " << pos << std::endl;
                break;
            
            case CHICKEN_MODEL:
                PlayerSystem::createChicken(pos);
                std::cout << "Chicken created in pos: " << pos << std::endl;
                break;

            default:
                break;
        }

        isClicking = true;
    }
    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
        isClicking = false;
    
    if(currentDummyModel != -1)
    {
        float xPos = (float)mouseXPos;
        float yPos = (float)mouseYPos;

        PlayerSystem::dummy->transform->position = RenderingSystem::from2DPosition(glm::vec2(xPos, yPos));
        PlayerSystem::dummy->meshRenderer->index = currentDummyModel;
        PlayerSystem::dummy->meshRenderer->isVisible = true;
    }
    else
        PlayerSystem::dummy->meshRenderer->isVisible = false;
    
    glfwPollEvents();
}

void InputSystem::destroy()
{
    saveValueToFile<uint32>(screenshotCount, "sc");
    std::cout << "Input system Destroyed" << std::endl;
}

template <typename T>
T InputSystem::loadValueFromFile(const String& filename)
{
    T value;
    std::ifstream file;

    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        file.open("meta/" + filename + ".meta");
        file >> value;
        file.close();
    }
    catch(const std::ifstream::failure& e)
    {
        std::cerr << "Error loading meta! " << e.what() << std::endl;
    }

    return value;
}

template <typename T>
void InputSystem::saveValueToFile(const T& value, const String& filename)
{
    std::ofstream file;
    try
    {
        file.open("meta/" + filename + ".meta");
        file << value;
        file.close();
    }
    catch(const std::ofstream::failure& e)
    {
        std::cerr << "Error saving meta! " << e.what() << std::endl;
    }
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
