#ifndef COMMON_H
#define COMMON_H

// ENTITIES
// ------------------------
#define EMPTY_ENTITY    0
#define CAMERA_ENTITY   1
#define UNIT_ENTITY     2
#define BUILDING_ENTITY 3
// ------------------------

// 3D MODELS | UNITS
// ------------------------
#define NO_MODEL -1
#define UNKNOWN   0
#define TREE01    1
#define TREE02    2
#define CHICKEN   3
#define VILLAGER  4
#define SOLDIER   5
#define BOWMAN    6
// 3D MODELS | BUILDINGS
// ------------------------
#define CASTLE    7
#define BARRACKS  8
#define ARCHERY   9
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

#endif // COMMON_H
