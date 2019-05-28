GLFWwindow* RenderingSystem::window = NULL;
Camera* RenderingSystem::mainCamera = NULL;
Shader RenderingSystem::shader;
Vector<Model*> RenderingSystem::models;

void RenderingSystem::init()
{
    // Create a Display for OpenGL 3.3
    initDisplay(3);

    mainCamera = new Camera;
    mainCamera->init(0);

    mainCamera->transform->position = { 0.0f, 4.0f, 8.0f };

    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

    shader.initShader("lightingShader");

    // After Setup
    shader.use();

    // Setting up Fragment Shader Uniforms
    shader.setVec3("viewPos", mainCamera->transform->position);

    // Light Parameters
    // Directional Light
    shader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);

    // Light Intensity
    shader.setVec3("dirLight.ambient", 0.2f, 0.2f, 0.2f);
    shader.setVec3("dirLight.diffuse", 0.5f, 0.5f, 0.5f);
    shader.setVec3("dirLight.specular", 1.0f, 1.0f, 1.0f);

    // Point Light
    shader.setInt("nrPointLights", 1);

    shader.setVec3( "pointLights[0].position", lightPos);

    shader.setVec3( "pointLights[0].ambient", 0.2f, 0.2f, 0.2f);
    shader.setVec3( "pointLights[0].diffuse", 0.5f, 0.5f, 0.5f);
    shader.setVec3( "pointLights[0].specular", 1.0f, 1.0f, 1.0f);

    shader.setFloat("pointLights[0].constant", 1.0f);
    shader.setFloat("pointLights[0].linear", 0.09f);
    shader.setFloat("pointLights[0].quadratic", 0.032f);

    // Spot Light
    shader.setVec3("spotLight.position", mainCamera->transform->position);
    shader.setVec3("spotLight.direction", glm::vec3(0.0f, 0.0f, 0.0f));

    shader.setVec3("spotLight.ambient", 0.2f, 0.2f, 0.2f);
    shader.setVec3("spotLight.diffuse", 0.5f, 0.5f, 0.5f);
    shader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);

    shader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
    shader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(17.5f)));

    shader.setFloat("spotLight.constant", 1.0f);
    shader.setFloat("spotLight.linear", 0.09f);
    shader.setFloat("spotLight.quadratic", 0.032f);

    shader.setFloat("material.shininess", 64);

    // --------------------------------------------------------------------------

    models.push_back(new Model("res/models/villager/villager.obj")); // 0
    models.push_back(new Model("res/models/chicken/chicken.obj")); // 1
    models.push_back(new Model("res/models/tree/tree.obj")); // 2

    // --------------------------------------------------------------------------
}

void RenderingSystem::update()
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view  = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    // Setting the Camera
    view = glm::lookAt(mainCamera->transform->position, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    if(mainCamera->cameraComponent->perspective)
        projection = glm::perspective(mainCamera->cameraComponent->fov, // FOV
                                      800.0f / 600.0f, // Aspect
                                      mainCamera->cameraComponent->cNear, // NEAR
                                      mainCamera->cameraComponent->cFar); // FAR
    else
        projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f,
                                mainCamera->cameraComponent->cNear, // NEAR
                                mainCamera->cameraComponent->cFar); // FAR

    shader.use();

    // Setting up Vertex Shader Uniforms
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);

    List<BaseComponent*>& memory = ComponentManager::getComponentMemory<MeshRenderer>();
    MeshRenderer* current;
    List<BaseComponent*>::iterator i;
    for(i = memory.begin(); i != memory.end(); ++i)
    {
        current = (MeshRenderer*)(*i);
        if(current->isVisible)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, current->entity->transform->position);
            model = glm::rotate(model, glm::radians(current->entity->transform->rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
            model = glm::rotate(model, glm::radians(current->entity->transform->rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::rotate(model, glm::radians(current->entity->transform->rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::scale(model, current->entity->transform->scale);
            shader.setMat4("model", model);
            models[current->index]->render(shader);
        }
    }

    glfwSwapBuffers(window);
}

void RenderingSystem::destroy()
{
    mainCamera->destroy();
    delete mainCamera;

    for(size_t i = 0; i < models.size(); ++i)
        delete models[i];

    glfwTerminate();
}

bool RenderingSystem::isActive()
{
    return !glfwWindowShouldClose(window);
}

void RenderingSystem::stop()
{
    glfwSetWindowShouldClose(window, GL_TRUE);
}

GLFWwindow* RenderingSystem::getContextWindow()
{
    return window;
}

void RenderingSystem::initDisplay(uint32 glVersion)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glVersion);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif // __APPLE__

    window = glfwCreateWindow(800, 600, "The Rise of Hullstorm", NULL, NULL);
    if(window == NULL)
    {
        std::cerr << "Unable to create window!" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize glad!" << std::endl;
        glfwTerminate();
        return;
    }

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
}

void RenderingSystem::framebufferSizeCallback(GLFWwindow* _window, int32 width, int32 height)
{
    glViewport(0, 0, width, height);
}
