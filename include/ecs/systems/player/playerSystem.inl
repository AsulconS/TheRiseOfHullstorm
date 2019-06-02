Unit* PlayerSystem::dummy;

void PlayerSystem::init()
{
    dummy = new Unit;
    dummy->init(0);

    dummy->meshRenderer->isVisible = false;
    dummy->transform->scale = { 0.15f, 0.15f, 0.15f };
}

void PlayerSystem::update(float deltaTime)
{
    //
}

void PlayerSystem::destroy()
{
    dummy->destroy();
    delete dummy;
}

void PlayerSystem::createVillager(const glm::vec3& pos)
{
    UnitSystem::createVillager(pos);
}

void PlayerSystem::createChicken(const glm::vec3& pos)
{
    UnitSystem::createChicken(pos);
}
