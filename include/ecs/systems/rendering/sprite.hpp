#ifndef ECS_RENDERING_SPRITE_H
#define ECS_RENDERING_SPRITE_H

#include <glm/glm.hpp>

#include "system/common.hpp"
#include "dataStructures.hpp"
#include "ecs/systems/rendering/shader.hpp"
#include "ecs/systems/rendering/renderingSystem.hpp"

class Sprite
{
public:
    void init(uint32 width, uint32 height, const glm::vec2& pos, const String& path, const String& name);
    void destroy();
    void render(Shader& shader);

    void setTexture(const String& path, const String& name);
    void setPosition(const glm::vec2& pos);

private:
    uint32 VAO;
    uint32 VBO;
    uint32 EBO;

    uint32 texture;
    String texturePath;
    String textureName;

    Vector<float> vertices;
    Vector<uint32> indices;

    glm::vec2 position;
};

#endif // ECS_RENDERING_SPRITE
