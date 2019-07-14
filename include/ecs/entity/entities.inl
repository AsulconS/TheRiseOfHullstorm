// ENTITIES
// --------

void Entity::internalInit(uint32 _id, uint32 _type)
{
    this->id = _id;
    this->type = _type;
    transform = ComponentManager::createComponent<Transform>(this);

    transform->position = { 0.0f, 0.0f, 0.0f };
    transform->rotation = { 0.0f, 0.0f, 0.0f };
    transform->scale    = { 4.0f, 4.0f, 4.0f };

    transform->target   = { 0.0f, 0.0f, 0.0f };

    transform->isStatic = false;

    EntityManagerLogger::increaseCreatedGlobalEntitiesCounter();
}

void EmptyEntity::init(uint32 _id)
{
    internalInit(_id, EMPTY_ENTITY);
}

void EmptyEntity::destroy()
{
    if(!ComponentManager::deleteComponent<Transform>(this))
        std::cerr << "Something went wrong with this entity!" << std::endl;
    
    EntityManagerLogger::increaseDestroyedGlobalEntitiesCounter();
}

void Camera::init(uint32 _id)
{
    internalInit(_id, CAMERA_ENTITY);

    cameraComponent = ComponentManager::createComponent<CameraComponent>(this);
    cameraComponent->mainCamera = true;
    cameraComponent->perspective = true;
    cameraComponent->fov = 45.0f;
    cameraComponent->cNear = 0.1f;
    cameraComponent->cFar = 1000.0f;
}

void Camera::destroy()
{
    if(!ComponentManager::deleteComponent<Transform>(this))
        std::cerr << "Something went wrong with this entity!" << std::endl;
    if(!ComponentManager::deleteComponent<CameraComponent>(this))
        std::cerr << "Something went wrong with this entity!" << std::endl;
    
    EntityManagerLogger::increaseDestroyedGlobalEntitiesCounter();
}

void Unit::init(uint32 _id)
{
    internalInit(_id, UNIT_ENTITY);

    meshRenderer = ComponentManager::createComponent<MeshRenderer>(this);
    meshRenderer->index = UNKNOWN;
    meshRenderer->alpha = 1.0f;
    meshRenderer->isVisible = true;

    circleCollider = ComponentManager::createComponent<CircleCollider2D>(this);
    circleCollider->radius = 4.0f;
    circleCollider->isSolid = true;
    circleCollider->isTrigger = false;

    stats = ComponentManager::createComponent<Stats>(this);
    stats->hp       = 100.0f;
    stats->damage   = 20.0f;
    stats->defense  = 10.0f;
    stats->velocity = 1.0f;
}

void Unit::destroy()
{
    if(!ComponentManager::deleteComponent<Transform>(this))
        std::cerr << "Something went wrong with this entity!" << std::endl;
    if(!ComponentManager::deleteComponent<MeshRenderer>(this))
        std::cerr << "Something went wrong with this entity!" << std::endl;
    if(!ComponentManager::deleteComponent<CircleCollider2D>(this))
        std::cerr << "Something went wrong with this entity!" << std::endl;
    if(!ComponentManager::deleteComponent<Stats>(this))
        std::cerr << "Something went wrong with this entity!" << std::endl;
    
    EntityManagerLogger::increaseDestroyedGlobalEntitiesCounter();
}

void Building::init(uint32 _id)
{
    internalInit(_id, BUILDING_ENTITY);

    meshRenderer = ComponentManager::createComponent<MeshRenderer>(this);
    meshRenderer->index = UNKNOWN;
    meshRenderer->alpha = 1.0f;
    meshRenderer->isVisible = true;

    boxCollider = ComponentManager::createComponent<BoxCollider2D>(this);
    boxCollider->size = { 8.0f, 0.0f, 8.0f };
    boxCollider->isSolid = true;
    boxCollider->isTrigger = false;

    stats = ComponentManager::createComponent<Stats>(this);
    stats->hp       = 1000.0f;
    stats->damage   = 0.0f;
    stats->defense  = 100.0f;
    stats->velocity = 0.0f;

    unitType = UNKNOWN;
}

void Building::destroy()
{
    if(!ComponentManager::deleteComponent<Transform>(this))
        std::cerr << "Something went wrong with this entity!" << std::endl;
    if(!ComponentManager::deleteComponent<MeshRenderer>(this))
        std::cerr << "Something went wrong with this entity!" << std::endl;
    if(!ComponentManager::deleteComponent<BoxCollider2D>(this))
        std::cerr << "Something went wrong with this entity!" << std::endl;
    if(!ComponentManager::deleteComponent<Stats>(this))
        std::cerr << "Something went wrong with this entity!" << std::endl;
    
    EntityManagerLogger::increaseDestroyedGlobalEntitiesCounter();
}

void Destructible::init(uint32 _id)
{
    internalInit(_id, DESTRUCTIBLE_ENTITY);

    meshRenderer = ComponentManager::createComponent<MeshRenderer>(this);
    meshRenderer->index = UNKNOWN;
    meshRenderer->alpha = 1.0f;
    meshRenderer->isVisible = true;

    circleCollider = ComponentManager::createComponent<CircleCollider2D>(this);
    circleCollider->radius = 4.0f;
    circleCollider->isSolid = true;
    circleCollider->isTrigger = false;
}

void Destructible::destroy()
{
    if(!ComponentManager::deleteComponent<Transform>(this))
        std::cerr << "Something went wrong with this entity!" << std::endl;
    if(!ComponentManager::deleteComponent<MeshRenderer>(this))
        std::cerr << "Something went wrong with this entity!" << std::endl;
    if(!ComponentManager::deleteComponent<CircleCollider2D>(this))
        std::cerr << "Something went wrong with this entity!" << std::endl;
    
    EntityManagerLogger::increaseDestroyedGlobalEntitiesCounter();
}
