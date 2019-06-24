#ifndef ECS_H
#define ECS_H

#include "ecs/component/componentManager.hpp"
#include "ecs/entities/entityManager.hpp"

#include "ecs/systems/rendering/renderingSystem.hpp"
#include "ecs/systems/rendering/shader.hpp"
#include "ecs/systems/rendering/mesh.hpp"
#include "ecs/systems/rendering/model.hpp"
#include "ecs/systems/rendering/sprite.hpp"

#include "ecs/systems/unit/abstractFactory.hpp"
#include "ecs/systems/unit/environmentFactory.hpp"
#include "ecs/systems/unit/humanFactory.hpp"
#include "ecs/systems/unit/unitSystem.hpp"

#ifndef ECS_LEGACY
    #include "ecs/systems/input/inputSystem.hpp"
#else
    #include "legacy/ecs/systems/input/inputSystem.hpp"
#endif

#include "ecs/systems/mechanics/movementSystem.hpp"
#include "ecs/systems/mechanics/mapSystem.hpp"

#include "ecs/systems/player/playerSystem.hpp"

#ifdef ECS_IMPLEMENTATION
    #include "ecs/component/componentManager.inl"
    #include "ecs/entities/entityManager.inl"

    #include "ecs/systems/rendering/renderingSystem.inl"
    #include "ecs/systems/rendering/shader.inl"
    #include "ecs/systems/rendering/mesh.inl"
    #include "ecs/systems/rendering/model.inl"
    #include "ecs/systems/rendering/sprite.inl"

    #include "ecs/systems/unit/abstractFactory.inl"
    #include "ecs/systems/unit/environmentFactory.inl"
    #include "ecs/systems/unit/humanFactory.inl"
    #include "ecs/systems/unit/unitSystem.inl"

    #ifndef ECS_LEGACY
        #include "ecs/systems/input/inputSystem.inl"
    #else
        #include "legacy/ecs/systems/input/inputSystem.inl"
    #endif

    #include "ecs/systems/mechanics/movementSystem.inl"
    #include "ecs/systems/mechanics/mapSystem.inl"

    #include "ecs/systems/player/playerSystem.inl"
#endif

#endif // ECS_H
