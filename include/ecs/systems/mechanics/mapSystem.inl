Vector<String> MapSystem::mapFiles;

void MapSystem::init(bool mapsOnLoad)
{
    mapFiles.push_back("");

    if(mapsOnLoad)
        loadMaps();
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

    uint32 marker;
    uint32 count;
    float  param;

    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    std::stringstream mapStream(mapFiles[index]);

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
                    break;
            }
        }
        mapStream >> marker;
    }
}

void MapSystem::loadMaps()
{
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
            mapFiles.push_back(loadMapFromFile("res/maps/" + filename));
            filedir = readdir(directory);
        }
        closedir(directory);
    }
    else
        perror("Could not open the directory!");
}

String MapSystem::loadMapFromFile(const String& path)
{
    String code;
    std::ifstream mapFile;

    mapFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        mapFile.open(path);
        std::stringstream shaderStream;
        shaderStream << mapFile.rdbuf();
        mapFile.close();
        code = shaderStream.str();
    }
    catch(std::ifstream::failure e)
    {
        std::cerr << "Error loading shader! " << e.what() << std::endl;
    }

    return code;
}
