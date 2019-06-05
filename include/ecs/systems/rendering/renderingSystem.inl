// Static Initializations
// ------------------------------------------------------

GLFWwindow* RenderingSystem::window = NULL;
Camera* RenderingSystem::mainCamera = NULL;
glm::mat4 RenderingSystem::projection = glm::mat4(1.0f);
glm::mat4 RenderingSystem::view = glm::mat4(1.0f);
glm::vec3 RenderingSystem::cameraFront;

uint32 RenderingSystem::windowWidth = 1280;
uint32 RenderingSystem::windowHeight = 720;

Shader RenderingSystem::shader;
Shader RenderingSystem::hudShader;
Sprite RenderingSystem::hud;
Sprite RenderingSystem::cursor;

Vector<Model*> RenderingSystem::models;

// ------------------------------------------------------

void RenderingSystem::init(uint32 width, uint32 height, bool fullScreen, uint32 glVersion)
{
    // Create a Display for OpenGL 3.3
    // -------------------------------
    initDisplay(width, height, fullScreen, glVersion);

    if(width && height)
        centerWindow();

    shader.initShader("lightingShader");
    hudShader.initShader("hudShader");

    // Loading HUD
    // -----------
    String folder = "res/hud/" + std::to_string(windowWidth) + 'x' + std::to_string(windowHeight);
    hud.init(windowWidth, windowHeight, glm::vec2(windowWidth / 2, windowHeight / 2), folder, "hud1.png");

    // Loading Cursor
    // --------------
    folder = "res/hud/cursors";
    cursor.init(64, 64, glm::vec2(windowWidth / 2, windowHeight / 2), folder, "lightblue_cursor.png");

    setupCamera();
    setupLights();

    // Loading Models
    // ---------------------------------------------------------------------------------

    models.push_back(new Model("res/models/primitives/cube.obj"));      // 0 : DEFAULT
    models.push_back(new Model("res/models/villager/villager.obj"));    // 1 : VILLAGER
    models.push_back(new Model("res/models/chicken/chicken.obj"));      // 2 : CHICKEN
    models.push_back(new Model("res/models/tree/tree.obj"));            // 3 : TREE

    // ---------------------------------------------------------------------------------
}

void RenderingSystem::update(float deltaTime)
{
    // Setup and Clear the Color and the Buffers
    // -----------------------------------------
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 model = glm::mat4(1.0f);

    // Setting the Camera
    view = glm::lookAt(mainCamera->transform->position, glm::vec3(mainCamera->transform->position + cameraFront), glm::vec3(0.0f, 1.0f, 0.0f));
    projection = glm::perspective(mainCamera->cameraComponent->fov, // FOV
                                  (float)windowWidth / (float)windowHeight, // Aspect
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
            shader.setFloat("alpha", current->alpha);
            models[current->index]->render(shader);
        }
    }

    glClear(GL_DEPTH_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);

    hudShader.use();
    hud.render(hudShader);
    cursor.render(hudShader);

    glfwSwapBuffers(window);
}

void RenderingSystem::destroy()
{
    mainCamera->destroy();
    delete mainCamera;

    for(size_t i = 0; i < models.size(); ++i)
        delete models[i];
    
    hud.destroy();
    cursor.destroy();

    glfwTerminate();
}

glm::vec3 RenderingSystem::from2DPosition(const glm::vec2& pos)
{
    glm::vec3 ray = rayCast(pos);

    glm::vec3 yVec = glm::vec3(0.0f, -mainCamera->transform->position.y, 0.0f);
    glm::vec3 target = mainCamera->transform->position.y * mainCamera->transform->position.y / glm::dot(yVec, ray) * ray;
    glm::vec3 finalPos = mainCamera->transform->position + target; finalPos.y = 0.0f;

    return finalPos;
}

glm::vec3 RenderingSystem::rayCast(const glm::vec2& pos)
{
    // Normalize Coords (To NDC Space)
    float mappedX = (2.0f * pos.x) / windowWidth - 1.0f;
    float mappedY = 1.0f - (2.0f * pos.y) / windowHeight;

    // To Homogeneus Clip Space Coords
    glm::vec4 clipSpaceCoords(mappedX, mappedY, -1.0f, 1.0f);

    // To Eye Space
    glm::vec4 eyeSpaceCoords = glm::inverse(projection) * clipSpaceCoords;
    eyeSpaceCoords.z = -1.0f;
    eyeSpaceCoords.w = 0.0f;

    // To World Space
    glm::vec4 worldSpaceCoords = glm::inverse(view) * eyeSpaceCoords;
    glm::vec3 ray = glm::normalize(glm::vec3(worldSpaceCoords.x, worldSpaceCoords.y, worldSpaceCoords.z));

    return ray;
}

void RenderingSystem::setupCamera()
{
    mainCamera = new Camera;
    mainCamera->init(0);

    mainCamera->transform->position = { 0.0f, 55.0f, 55.0f };
    mainCamera->transform->rotation = { -45.0f, 180.0f, 0.0f };

    cameraFront.x = glm::cos(glm::radians(mainCamera->transform->rotation.x)) * glm::sin(glm::radians(mainCamera->transform->rotation.y));
    cameraFront.y = glm::sin(glm::radians(mainCamera->transform->rotation.x));
    cameraFront.z = glm::cos(glm::radians(mainCamera->transform->rotation.x)) * glm::cos(glm::radians(mainCamera->transform->rotation.y));
}

void RenderingSystem::setupLights()
{
    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

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
    shader.setVec3("spotLight.direction", glm::vec3(mainCamera->transform->position + cameraFront));

    shader.setVec3("spotLight.ambient", 0.2f, 0.2f, 0.2f);
    shader.setVec3("spotLight.diffuse", 0.5f, 0.5f, 0.5f);
    shader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);

    shader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
    shader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(17.5f)));

    shader.setFloat("spotLight.constant", 1.0f);
    shader.setFloat("spotLight.linear", 0.09f);
    shader.setFloat("spotLight.quadratic", 0.032f);

    shader.setFloat("material.shininess", 64);
}

bool RenderingSystem::isActive()
{
    return !glfwWindowShouldClose(window);
}

void RenderingSystem::stop()
{
    glfwSetWindowShouldClose(window, GL_TRUE);
}

void RenderingSystem::centerWindow()
{
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();

    if(monitor == NULL)
        return;
    
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    if(mode == NULL)
        return;
    
    int32 monitorX;
    int32 monitorY;
    glfwGetMonitorPos(monitor, &monitorX, &monitorY);

    glfwSetWindowPos(window, monitorX + (mode->width - windowWidth) / 2, monitorY + (mode->height - windowHeight) / 2);
}

void RenderingSystem::initDisplay(uint32 width, uint32 height, bool fullScreen, uint32 glVersion)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glVersion);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif // __APPLE__

    bool autoSize = !width || !height;
    const GLFWvidmode* mode = (autoSize) ? glfwGetVideoMode(glfwGetPrimaryMonitor()) : NULL;

    windowWidth = (autoSize) ? mode->width : width;
    windowHeight = (autoSize) ? mode->height : height;
    window = glfwCreateWindow(windowWidth, windowHeight, "The Rise of Hullstorm", (fullScreen) ? glfwGetPrimaryMonitor() : NULL, NULL);
    if(window == NULL)
    {
        std::cerr << "Unable to create window!" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize glad!" << std::endl;
        glfwTerminate();
        return;
    }

    glDisable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

uint32 RenderingSystem::loadTextureFromFile(const char* _filename, const String& directory, bool isFlipped)
{
    uint32 texture;
    String filename = String(_filename);
    String path = directory + '/' + filename;

    glGenTextures(1, &texture);
    int width, height, nrComponents;
    stbi_set_flip_vertically_on_load(isFlipped);
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
    // Load RAW Data
    if(data)
    {
        GLenum format;
        if(nrComponents == 1)
            format = GL_RED;
        else if(nrComponents == 3)
            format = GL_RGB;
        else if(nrComponents == 4)
            format = GL_RGBA;
        
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cerr << "Failed to load texture" << std::endl;
        stbi_image_free(data);
    }

    return texture;
}

void RenderingSystem::saveScreenshot(const String& filename)
{
    uint8* data = new uint8[3 * windowWidth * windowHeight];
    glReadPixels(0, 0, windowWidth, windowHeight, GL_RGB, GL_UNSIGNED_BYTE, data);
    stbi_flip_vertically_on_write(true);
    stbi_write_jpg(filename.c_str(), windowWidth, windowHeight, 3, data, windowWidth * 3);
    delete[] data;
}

void RenderingSystem::framebufferSizeCallback(GLFWwindow* _window, int32 width, int32 height)
{
    windowWidth = width;
    windowHeight = height;
    glViewport(0, 0, windowWidth, windowHeight);
}
