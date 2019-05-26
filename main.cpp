#define  ECS_IMPLEMENTATION
#include "ecs.hpp"

int main()
{
    MovementSystem::init();
    MovementSystem::update();
    MovementSystem::destroy();

    return 0;
}
