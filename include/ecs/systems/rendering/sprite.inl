void Sprite::init(uint32 width, uint32 height, const glm::vec2& pos, const String& path, const String& name)
{
    float mappedHalfWidth  = (float)width  / (float)RenderingSystem::windowWidth;
    float mappedHalfHeight = (float)height / (float)RenderingSystem::windowHeight;

    vertices =
    {
        // Position                           // UV
         mappedHalfWidth,  mappedHalfHeight,  1.0f, 1.0f,   // Top Right
         mappedHalfWidth, -mappedHalfHeight,  1.0f, 0.0f,   // Bottom Right
        -mappedHalfWidth, -mappedHalfHeight,  0.0f, 0.0f,   // Bottom Left
        -mappedHalfWidth,  mappedHalfHeight,  0.0f, 1.0f    // Top Left
    };

    indices =
    {
        2, 1, 3, 3, 1, 0
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32), &indices[0], GL_STATIC_DRAW);

    // Vertex Position
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Vertex UV
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    position = pos;
    setTexture(path, name);
}

void Sprite::render(Shader& shader)
{
    glActiveTexture(GL_TEXTURE0);

    shader.setFloat("spriteTexture", 0);

    float mappedX = (2.0f * position.x) / RenderingSystem::windowWidth - 1.0f;
    float mappedY = 1.0f - (2.0f * position.y) / RenderingSystem::windowHeight;
    shader.setVec2("offset", mappedX, mappedY);
    glBindTexture(GL_TEXTURE_2D, texture);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);
}

void Sprite::destroy()
{
    glDeleteTextures(1, &texture);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Sprite::setTexture(const String& path, const String& name)
{
    if(glIsTexture(texture))
        glDeleteTextures(1, &texture);

    texturePath = path;
    textureName = name;
    texture = RenderingSystem::loadTextureFromFile(textureName.c_str(), texturePath, true);
}

void Sprite::setPosition(const glm::vec2& pos)
{
    position = pos;
}
