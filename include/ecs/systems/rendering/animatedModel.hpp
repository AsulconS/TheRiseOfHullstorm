#ifndef ECS_ANIMATED_MODEL_H
#define ECS_ANIMATED_MODEL_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "ecs/systems/rendering/model.hpp"

class AnimatedModel : public Model
{
public:
    AnimatedModel(const String& path) : Model(path) {}
    virtual ~AnimatedModel() {}
};

#endif // ECS_ANIMATED_MODEL_H
