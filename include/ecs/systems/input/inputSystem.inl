// Static Initializations
// ----------------------------------------

GLFWwindow* InputSystem::window = NULL;
uint32 InputSystem::screenshotCount = 0;

double InputSystem::mouseXPos;
double InputSystem::mouseYPos;
double InputSystem::lastMouseXPos;
double InputSystem::lastMouseYPos;
double InputSystem::virtualXPos;
double InputSystem::virtualYPos;

bool InputSystem::isClicking = false;
bool InputSystem::isSaving = false;

uint32 InputSystem::currentDummy = NO_MODEL;

// ----------------------------------------

void InputSystem::init()
{
    window = RenderingSystem::window;
    glfwSetScrollCallback(window, scrollCallback);

    virtualXPos = RenderingSystem::windowWidth / 2;
    virtualYPos = RenderingSystem::windowHeight / 2;
    
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwGetCursorPos(window, &lastMouseXPos, &lastMouseYPos);

    RenderingSystem::cursor.setPosition(glm::vec2((float)virtualXPos, (float)virtualYPos));

    screenshotCount = loadValueFromFile<uint32>("sc");
}

void InputSystem::update(float deltaTime)
{
    // Mouse Pre-Calculations
    // ---------------------------------------------------------
    mouseBoundingsCalculation(deltaTime);
    float xPos = (float)virtualXPos;
    float yPos = (float)virtualYPos;

    RenderingSystem::cursor.setPosition(glm::vec2(xPos, yPos));
    // ---------------------------------------------------------

    // Exit Processing
    // ----------------------------------------------------
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        RenderingSystem::stop();
    // ----------------------------------------------------
    
    // Screenshot Processing
    // -------------------------------------------------------------------------------------------------------------
    if(glfwGetKey(window, GLFW_KEY_F12) == GLFW_PRESS && !isSaving)
    {
        std::cout << "Saving Screenshot . . ." << std::endl;
        RenderingSystem::saveScreenshot("screenshots/screenshot-" + std::to_string(screenshotCount++) + ".jpg");
        std::cout << "Screenshot Saved Successfully!" << std::endl;

        isSaving = true;
    }
    if(glfwGetKey(window, GLFW_KEY_F12) == GLFW_RELEASE)
        isSaving = false;
    // -------------------------------------------------------------------------------------------------------------
    
    // Camera Keyboard-Directional Movement
    // ---------------------------------------------------------------------------
    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        RenderingSystem::mainCamera->transform->position.z -= 64.0f * deltaTime;
    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        RenderingSystem::mainCamera->transform->position.z += 64.0f * deltaTime;
    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        RenderingSystem::mainCamera->transform->position.x += 64.0f * deltaTime;
    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        RenderingSystem::mainCamera->transform->position.x -= 64.0f * deltaTime;
    // ---------------------------------------------------------------------------
    
    // Dummy Model
    // -----------------------------------------------
    if(glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
        currentDummy = UNKNOWN;
    if(glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        currentDummy = TREE01;
    if(glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        currentDummy = TREE02;
    if(glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
        currentDummy = TREE03;
    if(glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
        currentDummy = MINE;
    if(glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
        currentDummy = CHICKEN;
    if(glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
        currentDummy = VILLAGER;
    if(glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
        currentDummy = SOLDIER;
    if(glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
        currentDummy = BOWMAN;
    if(glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS)
        currentDummy = CASTLE;
    if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        currentDummy = BARRACKS;
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        currentDummy = ARCHERY;
    if(glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
        currentDummy = FARM;
    if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        currentDummy = NO_MODEL;
    // -----------------------------------------------
    
    // Dummy Creator
    // -------------------------------------------------------------------------------------------------------------------------
    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !isClicking && (currentDummy != NO_MODEL))
    {
        glm::vec3 pos = RenderingSystem::from2DPosition(glm::vec2(xPos, yPos));

        if(currentDummy < CHICKEN)
            UnitSystem::createUnit<EnvironmentFactory>(0, currentDummy, pos);
        else if(currentDummy < CASTLE)
            PlayerSystem::createUnit(currentDummy, pos);
        else
            PlayerSystem::createBuilding(currentDummy, pos);

        isClicking = true;
    }
    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS && !isClicking)
    {
        glm::vec3 pos = RenderingSystem::from2DPosition(glm::vec2(xPos, yPos));

        Unit* unit;
        List<BaseComponent*>& memory = ComponentManager::getComponentMemory<Transform>();
        List<BaseComponent*>::iterator i;
    
        for(i = memory.begin(); i != memory.end(); ++i)
        {
            if((*i)->entity->type != UNIT_ENTITY)
                continue;
            
            unit = (Unit*)((*i)->entity);
            unit->transform->target = pos;
        }
    }
    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
        isClicking = false;
    // -------------------------------------------------------------------------------------------------------------------------
    
    // Dummy Constant Model
    // -----------------------------------------------------------------------------------------------------
    if(currentDummy != NO_MODEL)
    {
        PlayerSystem::dummy->transform->position = RenderingSystem::from2DPosition(glm::vec2(xPos, yPos));
        PlayerSystem::dummy->meshRenderer->index = currentDummy;
        PlayerSystem::dummy->meshRenderer->isVisible = true;
    }
    else
        PlayerSystem::dummy->meshRenderer->isVisible = false;
    // -----------------------------------------------------------------------------------------------------
    
    // Events Polled
    // ---------------
    glfwPollEvents();
}

void InputSystem::destroy()
{
    saveValueToFile<uint32>(screenshotCount, "sc");
    std::cout << "Input System Destroyed" << std::endl;
}

void InputSystem::mouseBoundingsCalculation(float deltaTime)
{
    glfwGetCursorPos(window, &mouseXPos, &mouseYPos);

    virtualXPos += mouseXPos - lastMouseXPos;
    virtualYPos += mouseYPos - lastMouseYPos;
    lastMouseXPos = mouseXPos;
    lastMouseYPos = mouseYPos;

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
