#ifndef CORE_COMMON_H
#define CORE_COMMON_H

// ENTITIES
// ----------------------------
#define EMPTY_ENTITY        0
#define PLAYER_ENTITY       1
#define CAMERA_ENTITY       2
#define UNIT_ENTITY         3
#define BUILDING_ENTITY     4
#define DESTRUCTIBLE_ENTITY 5
// ----------------------------

// 3D MODELS | UNITS
// ------------------------
#define NO_MODEL -1
#define UNKNOWN   0
#define TREE01    1
#define TREE02    2
#define TREE03    3
#define MINE      4
#define CHICKEN   5
#define VILLAGER  6
#define SOLDIER   7
#define BOWMAN    8
// 3D MODELS | BUILDINGS
// ------------------------
#define CASTLE    9
#define BARRACKS  10
#define ARCHERY   11
#define FARM      12
// ------------------------

// RACES
// ------------------------
#define HUMAN_RACE 0
#define OXIMORPH_RACE 1
// ------------------------

#define AUTO_SIZE 0, 0

#include <cstdint>
#include <type_traits>

using int8 = int8_t;
using uint8 = uint8_t;
using int16 = int16_t;
using uint16 = uint16_t;
using int32 = int32_t;
using uint32 = uint32_t;
using int64 = int64_t;
using uint64 = uint64_t;

using UnitType = uint32;
using BuildingType = uint32;
using DestructibleType = uint32;

#endif // CORE_COMMON_H
