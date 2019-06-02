GLFWwindow* InputSystem::window = NULL;

void InputSystem::init()
{
    window = RenderingSystem::getContextWindow();
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void InputSystem::update(float deltaTime)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        RenderingSystem::stop();
    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        RenderingSystem::mainCamera->transform->position.z -= 4.0f * deltaTime;;
    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        RenderingSystem::mainCamera->transform->position.z += 4.0f * deltaTime;;
    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        RenderingSystem::mainCamera->transform->position.x += 4.0f * deltaTime;;
    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        RenderingSystem::mainCamera->transform->position.x -= 4.0f * deltaTime;;
    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        float xPos = (float)x;
        float yPos = (float)y;

        glm::vec3 pos = RenderingSystem::from2DPosition(glm::vec2(xPos, yPos));

        UnitSystem::createVillager(pos);
    }
    
    glfwPollEvents();
}

void InputSystem::destroy()
{
    std::cout << "Input system Destroyed" << std::endl;
}
