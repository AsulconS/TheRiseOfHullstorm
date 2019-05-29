GLFWwindow* InputSystem::window = NULL;

void InputSystem::init()
{
    window = RenderingSystem::getContextWindow();
}

void InputSystem::update(float deltaTime)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        RenderingSystem::stop();
    if(glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
        UnitSystem::createVillager();
    if(glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
        UnitSystem::createChicken();
    
    glfwPollEvents();
}

void InputSystem::destroy()
{
    std::cout << "Input system Destroyed" << std::endl;
}
