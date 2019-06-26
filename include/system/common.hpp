#ifndef COMMON_H
#define COMMON_H

// ENTITIES
// ----------------------------
#define EMPTY_ENTITY        0
#define CAMERA_ENTITY       1
#define UNIT_ENTITY         2
#define BUILDING_ENTITY     3
#define DESTRUCTIBLE_ENTITY 4
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

typedef int8_t int8;
typedef uint8_t uint8;
typedef int16_t int16;
typedef uint16_t uint16;
typedef int32_t int32;
typedef uint32_t uint32;
typedef int64_t int64;
typedef uint64_t uint64;

typedef uint32 UnitType;
typedef uint32 BuildingType;
typedef uint32 DestructibleType;

#endif // COMMON_H
