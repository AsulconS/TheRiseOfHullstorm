#pragma once

#ifdef ECS_IMPLEMENTATION
	#define STB_IMAGE_IMPLEMENTATION
	#define STB_IMAGE_WRITE_IMPLEMENTATION
#endif

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "core/common.hpp"
#include "core/time.hpp"
#include "core/dataStructures.hpp"

#include "ecs/component/componentManager.hpp"
#include "ecs/component/components.hpp"
#include "ecs/entity/entityManager.hpp"
#include "ecs/entity/entities.hpp"

#include "ecs/systems/rendering/renderingSystem.hpp"
#include "ecs/systems/rendering/shader.hpp"
#include "ecs/systems/rendering/mesh.hpp"
#include "ecs/systems/rendering/model.hpp"
#include "ecs/systems/rendering/animatedModel.hpp"
#include "ecs/systems/rendering/sprite.hpp"

#include "ecs/systems/unit/abstractFactory.hpp"
#include "ecs/systems/unit/environmentFactory.hpp"
#include "ecs/systems/unit/humanFactory.hpp"
#include "ecs/systems/unit/oximorphFactory.hpp"
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
	#include "core/time/deltaTime.inl"

	#include "ecs/component/componentManager.inl"
	#include "ecs/entity/entityManager.inl"
	#include "ecs/entity/entities.inl"

	#include "ecs/systems/rendering/renderingSystem.inl"
	#include "ecs/systems/rendering/shader.inl"
	#include "ecs/systems/rendering/mesh.inl"
	#include "ecs/systems/rendering/model.inl"
	#include "ecs/systems/rendering/animatedModel.inl"
	#include "ecs/systems/rendering/sprite.inl"

	#include "ecs/systems/unit/abstractFactory.inl"
	#include "ecs/systems/unit/environmentFactory.inl"
	#include "ecs/systems/unit/humanFactory.inl"
	#include "ecs/systems/unit/oximorphFactory.inl"
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
