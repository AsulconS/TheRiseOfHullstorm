#ifndef ECS_MAP_SYSTEM_H
#define ECS_MAP_SYSTEM_H

#include <fstream>
#include <algorithm>

#ifdef _WIN32
    #include "system/dirent.h"
#else
    #include <dirent.h>
#endif

#include "ecs/component/componentManager.hpp"
#include "ecs/entities/entityManager.hpp"

class MapSystem
{
public:
    static void init(bool mapsOnLoad = true);
    static void update(float deltaTime);
    static void destroy();

    static void loadMap(uint32 index);

    static void loadMaps();

private:
    static Vector<String> mapFiles;

    static String loadMapFromFile(const String& filename);
};

#endif // ECS_MAP_SYSTEM_H
