#ifndef COMMON_H
#define COMMON_H

#define EMPTY_ENTITY  0
#define CAMERA_ENTITY 1
#define UNIT_ENTITY   2

#define DEFAULT_MODEL  0
#define VILLAGER_MODEL 1
#define CHICKEN_MODEL  2
#define TREE_MODEL     3

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

#endif // COMMON_H
