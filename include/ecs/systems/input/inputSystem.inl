GLFWwindow* InputSystem::window = NULL;

void InputSystem::init()
{
    window = RenderingSystem::getContextWindow();
}

void InputSystem::update()
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        RenderingSystem::stop();
    
    glfwPollEvents();
}

void InputSystem::destroy()
{
    std::cout << "Input system Destroyed" << std::endl;
}
