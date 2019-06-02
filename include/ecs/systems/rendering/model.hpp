#ifndef ECS_RENDERING_MODEL_H
#define ECS_RENDERING_MODEL_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "system/common.hpp"
#include "dataStructures.hpp"

class Model
{
public:
    Model(const String& path);
    virtual ~Model();

    void render(Shader& shader);

    static uint32 loadTextureFromFile(const char* filename, const String& directory, bool isFlipped);

private:
    // Model Data
    Vector<Mesh> meshes;
    Vector<Texture> texturesLoaded;
    String directory;

    void loadModel(const String& path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    Vector<Texture> loadMaterialTextures(aiMaterial* material, aiTextureType type, const String& typeName);
};

#endif // ECS_RENDERING_MODEL_H
