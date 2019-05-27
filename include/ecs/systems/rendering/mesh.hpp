#ifndef ECS_RENDERING_MESH_H
#define ECS_RENDERING_MESH_H

#include <glm/glm.hpp>

#include "system/common.hpp"
#include "dataStructures.hpp"
#include "ecs/systems/rendering/shader.hpp"

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 UV;
};

struct Texture
{
    uint32 ID;
    String type;
    String name;
};

class Mesh
{
public:
    Vector<Vertex> vertices;
    Vector<uint32> indices;
    Vector<Texture> textures;

    Mesh(Vector<Vertex>& _vertices, Vector<uint32>& _indices, Vector<Texture>& _textures);
    void freeMesh();

    void render(Shader& shader);

private:
    uint32 VAO, VBO, EBO;
    void setupMesh();
};

#endif // ECS_RENDERING_MESH_H
