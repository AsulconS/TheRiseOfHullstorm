#ifndef ECS_RENDERING_MODEL_H
#define ECS_RENDERING_MODEL_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "system/common.hpp"
#include "dataStructures.hpp"

#include "ecs/systems/rendering/mesh.hpp"
#include "ecs/systems/rendering/renderingSystem.hpp"

class Model
{
public:
    Model(const String& path);
    virtual ~Model();

    void render(Shader& shader);

private:
    // Model Data
    // ----------
    Vector<Mesh> meshes;
    Vector<Texture> texturesLoaded;
    String directory;

    // Internal Data Processing
    // ------------------------
    void loadModel(const String& path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    Vector<Texture> loadMaterialTextures(aiMaterial* material, aiTextureType type, const String& typeName);
};

#endif // ECS_RENDERING_MODEL_H
