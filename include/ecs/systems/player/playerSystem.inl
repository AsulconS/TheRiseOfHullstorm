Unit* PlayerSystem::dummy;
uint32 PlayerSystem::playerInstance = 1;

void PlayerSystem::init()
{
    dummy = new Unit;
    dummy->init(0);

    dummy->meshRenderer->alpha = 0.25f;
    dummy->meshRenderer->isVisible = false;
    dummy->circleCollider->isSolid = false;

    playerInstance = UnitSystem::registerPlayer();

    ConnectionSystem::setURL("http://localhost:8080/players");
    ConnectionSystem::registerPlayer();
}

void PlayerSystem::update(float deltaTime)
{
    //
}

void PlayerSystem::destroy()
{
    dummy->destroy();
    delete dummy;

    std::cout << "Player System Destroyed" << std::endl;
}

void PlayerSystem::createUnit(const UnitType unit, const glm::vec3& pos)
{
    UnitSystem::createUnit<HumanFactory>(playerInstance, unit, pos);
}

void PlayerSystem::createBuilding(const BuildingType building, const glm::vec3& pos)
{
    UnitSystem::createBuilding<HumanFactory>(playerInstance, building, pos);
}
