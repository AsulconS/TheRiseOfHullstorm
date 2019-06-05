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

/* Map System:
 * --------------
 * Entities: 0
 * Components: 0
 * -------------- */
class GameMap
{
public:
    String name;
    String data;

    inline explicit GameMap(const String& _name, const String& _data) : name(_name), data(_data) {}

    inline bool operator<(const GameMap& o) { return this->name < o.name; }
    inline bool operator>(const GameMap& o) { return this->name > o.name; }
};

class MapSystem
{
public:
    static void init(bool mapsOnLoad = true);
    static void update(float deltaTime);
    static void destroy();

    static void loadMap(uint32 index);

    static void loadMaps();

private:
    static Vector<GameMap> maps;

    static String loadMapFromFile(const String& filename);
};

#endif // ECS_MAP_SYSTEM_H
