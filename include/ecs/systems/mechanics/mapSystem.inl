Vector<GameMap> MapSystem::maps;

void MapSystem::init(bool mapsOnLoad)
{
    if(mapsOnLoad)
        loadMaps();
    
    std::sort(maps.begin(), maps.end());
}

void MapSystem::update(float deltaTime)
{
    //
}

void MapSystem::destroy()
{
    //
}

void MapSystem::loadMap(uint32 index)
{
    UnitSystem::clear();

    uint32 marker; // Holds the model
    uint32 count;  // Holds how many models to load

    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    std::stringstream mapStream(maps[index].data);

    mapStream >> marker;
    while(marker != -1)
    {
        mapStream >> count;
        for(size_t i = 0; i < count; ++i)
        {
            mapStream >> position.x;
            mapStream >> position.y;
            mapStream >> position.z;

            mapStream >> rotation.x;
            mapStream >> rotation.y;
            mapStream >> rotation.z;

            mapStream >> scale.x;
            mapStream >> scale.y;
            mapStream >> scale.z;

            switch(marker)
            {
                case VILLAGER_MODEL:
                    UnitSystem::createVillager(4.0f * position, rotation, scale);
                    break;
                
                case CHICKEN_MODEL:
                    UnitSystem::createChicken(4.0f * position, rotation, scale);
                    break;
                
                case TREE_MODEL:
                    UnitSystem::spawnTree(4.0f * position, rotation, scale);
                    break;
                
                default:
                    UnitSystem::createUnknown(4.0f * position, rotation, scale);
                    break;
            }
        }
        mapStream >> marker;
    }
}

void MapSystem::loadMaps()
{
    maps.clear();

    String filename;
    DIR* directory = opendir("res/maps");
    dirent* filedir;

    if(directory != NULL)
    {
        filedir = readdir(directory);
        while(filedir != NULL)
        {
            filename = filedir->d_name;
            if(filename == "." || filename == "..")
            {
                filedir = readdir(directory);
                continue;
            }
            maps.push_back(GameMap(filename, loadMapFromFile(filename)));
            filedir = readdir(directory);
        }
        closedir(directory);
    }
    else
        perror("Could not open the directory!");
}

String MapSystem::loadMapFromFile(const String& filename)
{
    String code;
    std::ifstream mapFile;

    mapFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        mapFile.open("res/maps/" + filename);
        std::stringstream shaderStream;
        shaderStream << mapFile.rdbuf();
        mapFile.close();
        code = shaderStream.str();
    }
    catch(const std::ifstream::failure& e)
    {
        std::cerr << "Error loading map! " << e.what() << std::endl;
    }

    return code;
}
