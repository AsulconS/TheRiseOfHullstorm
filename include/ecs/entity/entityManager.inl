// ENTITY MANAGER DEFINITIONS
// --------------------------

uint32 EntityManagerLogger::createdGlobalEntitiesCount = 0;
uint32 EntityManagerLogger::destroyedGlobalEntitiesCount = 0;

void EntityManagerLogger::outLog()
{
    std::cout << createdGlobalEntitiesCount << " entities created!" << std::endl;
    std::cout << destroyedGlobalEntitiesCount << " entities destroyed!" << std::endl;
}

template <typename E>
EntityManager<E>::~EntityManager()
{
    clear();
}

template <typename E>
E* EntityManager<E>::createEntity()
{
    // Ensure The Type is actually an Entity
    static_assert(std::is_base_of<Entity, E>::value, "The E type MUST be an Entity");

    E* entity = new E;
    entity->init(currentID++);

    entities.push_front(entity);

    return entity;
}

template <typename E>
bool EntityManager<E>::removeEntity(E* entity)
{
    List<Entity*>::iterator i;
    for(i = entities.begin(); i != entities.end(); ++i)
        if((*i)->id == entity->id)
        {
            (*i)->destroy();
            delete (*i);
            entities.erase(i);
            return true;
        }
    
    return false;
}

template <typename E>
void EntityManager<E>::clear()
{
    if(entities.empty())
        return;
    
    List<Entity*>::iterator i;
    for(i = entities.begin(); i != entities.end(); ++i)
    {
        (*i)->destroy();
        delete (*i);
    }
    entities.clear();
}
