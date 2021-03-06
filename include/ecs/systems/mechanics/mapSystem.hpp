#ifndef ECS_MAP_SYSTEM_H
#define ECS_MAP_SYSTEM_H

#include <fstream>
#include <algorithm>

#ifdef _WIN32
    #include "core/dirent.h"
#else
    #include <dirent.h>
#endif

#include "ecs/systems/unit/unitSystem.hpp"

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

    static void loadMap(uint32 index, bool external = true);

    static void loadMaps();

private:
    explicit MapSystem() {}

    static Vector<GameMap> maps;
    static uint32 neutralPlayerInstance;

    static String loadMapFromFile(const String& filename);
};

#endif // ECS_MAP_SYSTEM_H
