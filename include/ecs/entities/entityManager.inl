// ENTITIES
// --------

void Entity::internalInit(uint32 _id, uint32 _type)
{
    this->id = _id;
    this->type = _type;
    transform = ComponentManager::createComponent<Transform>(this);

    transform->position = { 0.0f, 0.0f, 0.0f };
    transform->rotation = { 0.0f, 0.0f, 0.0f };
    transform->scale    = { 1.0f, 1.0f, 1.0f };

    transform->isStatic = false;
}

void EmptyEntity::init(uint32 _id)
{
    internalInit(_id, EMPTY_ENTITY);
}

void EmptyEntity::destroy()
{
    if(!ComponentManager::deleteComponent<Transform>(this))
        std::cerr << "Something went wrong with this entity!" << std::endl;
}

void Camera::init(uint32 _id)
{
    internalInit(_id, CAMERA_ENTITY);

    cameraComponent = ComponentManager::createComponent<CameraComponent>(this);
    cameraComponent->mainCamera = true;
    cameraComponent->perspective = true;
    cameraComponent->fov = 45.0f;
    cameraComponent->cNear = 0.1f;
    cameraComponent->cFar = 100.0f;
}

void Camera::destroy()
{
    if(!ComponentManager::deleteComponent<Transform>(this))
        std::cerr << "Something went wrong with this entity!" << std::endl;
    if(!ComponentManager::deleteComponent<CameraComponent>(this))
        std::cerr << "Something went wrong with this entity!" << std::endl;
}

void Unit::init(uint32 _id)
{
    internalInit(_id, UNIT_ENTITY);

    meshRenderer = ComponentManager::createComponent<MeshRenderer>(this);
    meshRenderer->index = 0;
    meshRenderer->isVisible = true;

    stats = ComponentManager::createComponent<Stats>(this);
    stats->hp       = 100.0f;
    stats->damage   = 20.0f;
    stats->defense  = 10.0f;
    stats->velocity = 0.005f;
}

void Unit::destroy()
{
    if(!ComponentManager::deleteComponent<Transform>(this))
        std::cerr << "Something went wrong with this entity!" << std::endl;
    if(!ComponentManager::deleteComponent<MeshRenderer>(this))
        std::cerr << "Something went wrong with this entity!" << std::endl;
    if(!ComponentManager::deleteComponent<Stats>(this))
        std::cerr << "Something went wrong with this entity!" << std::endl;
}

std::ostream& operator<<(std::ostream& o, glm::vec3& v)
{
    o << '(' << v.x << ", " << v.y << ", " << v.z << ')';
    return o;
}

void EmptyEntity::print()
{
    std::cout << "TRANSFORM COMPONENT:\n--------------------" << std::endl;
    std::cout << "Position:\t";
    std::cout << transform->position << std::endl;
    std::cout << "Rotation:\t";
    std::cout << transform->rotation << std::endl;
    std::cout << "Scale:\t\t";
    std::cout << transform->scale << std::endl;
    std::cout << std::endl;
}

void Camera::print()
{
    //
}

void Unit::print()
{
    std::cout << "------------------------------------" << std::endl;
    std::cout << "Unit Nr. " << id << "                      ]" << std::endl;
    std::cout << "------------------------------------" << std::endl;

    std::cout << "TRANSFORM COMPONENT:\n--------------------" << std::endl;
    std::cout << "Position:\t";
    std::cout << transform->position << std::endl;
    std::cout << "Rotation:\t";
    std::cout << transform->rotation << std::endl;
    std::cout << "Scale:\t\t";
    std::cout << transform->scale << std::endl;
    std::cout << std::endl;

    std::cout << "STATS COMPONENT:\n--------------------" << std::endl;
    std::cout << "HP:\t\t";
    std::cout << stats->hp << std::endl;
    std::cout << "Damage:\t\t";
    std::cout << stats->damage << std::endl;
    std::cout << "Defense:\t";
    std::cout << stats->damage << std::endl;
    std::cout << "Velocity:\t";
    std::cout << stats->velocity << std::endl;

    std::cout << "------------------------------------" << std::endl;
}

// ENTITY MANAGER DEFINITIONS
// --------------------------

template <typename E>
E* EntityManager<E>::createEntity()
{
    // Ensure The Type is actually an Entity
    static_assert(std::is_base_of<Entity, E>::value, "The E type MUST be an Entity");

    E* entity = new E;
    entity->init(currentID++);

    entities.push_back(entity);

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
    List<Entity*>::iterator i;
    for(i = entities.begin(); i != entities.end(); ++i)
    {
        (*i)->destroy();
        delete (*i);
    }
    entities.clear();
}

template <typename E>
void EntityManager<E>::printEntities()
{
    List<Entity*>::iterator i;
    for(i = entities.begin(); i != entities.end(); ++i)
        (*i)->print();
}
