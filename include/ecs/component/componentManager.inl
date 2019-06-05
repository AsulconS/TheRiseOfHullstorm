// Regristation for components
// ---------------------------

uint32 ComponentManager::componentID = 0;
uint32 ComponentManager::globalComponentsCount = 0;
uint32 ComponentManager::destroyedGlobalComponentsCount = 0;
Vector<List<BaseComponent*>> ComponentManager::componentMemory;
List<BaseComponent*>::iterator ComponentManager::componentIt;

uint32 ComponentManager::registerComponentType()
{
    componentMemory.push_back(List<BaseComponent*>());
    return componentID++;
}

// The Components are registered into the Manager
// ----------------------------------------------
template <typename T>
const uint32 Component<T>::ID(ComponentManager::registerComponentType());

template <typename T>
const uint32 Component<T>::SIZE(sizeof(T));

template <typename C>
C* ComponentManager::createComponent(Entity* entity)
{
    // Static Assertion: The type must be a component
    static_assert(std::is_base_of<BaseComponent, C>::value, "|| THE C TYPE MUST BE A *COMPONENT* ||");

    C* component = new C;
    component->entity = entity;
    componentMemory[C::ID].push_front(component);

    ++globalComponentsCount;
    return component;
}

// Experimental Section
// --------------------------------------------------------------------------------------------------------

template <typename C>
C* ComponentManager::Experimental::registerComponent(C* component, Entity* entity)
{
    // Static Assertion: The type must be a component
    static_assert(std::is_base_of<BaseComponent, C>::value, "|| THE C TYPE MUST BE A *COMPONENT* ||");

    component->entity = entity;
    componentMemory[C::ID].push_front(component);

    ++globalComponentsCount;
    return component;
}

void ComponentManager::Experimental::clearMemory()
{
    for(size_t i = 0; i < componentMemory.size(); ++i)
    {
        for(componentIt = componentMemory[i].begin(); componentIt != componentMemory[i].end(); ++componentIt)
            delete (*componentIt);
        componentMemory[i].clear();
    }
}

// --------------------------------------------------------------------------------------------------------

template <typename C>
bool ComponentManager::deleteComponent(Entity* entity)
{
    // Static Assertion: The type must be a component
    static_assert(std::is_base_of<BaseComponent, C>::value, "|| THE C TYPE MUST BE A *COMPONENT* ||");

    for(componentIt = componentMemory[C::ID].begin(); componentIt != componentMemory[C::ID].end(); ++componentIt)
        if((*componentIt)->entity == entity)
        {
            delete (*componentIt);
            componentMemory[C::ID].erase(componentIt);
            ++destroyedGlobalComponentsCount;
            return true;
        }
    
    return false;
}

template <typename C>
List<BaseComponent*>& ComponentManager::getComponentMemory()
{
    // Static Assertion: The type must be a component
    static_assert(std::is_base_of<BaseComponent, C>::value, "|| THE C TYPE MUST BE A *COMPONENT* ||");

    return componentMemory[C::ID];
}

void ComponentManager::outLog()
{
    std::cout << globalComponentsCount << " components created!" << std::endl;
    std::cout << destroyedGlobalComponentsCount << " components destroyed!" << std::endl;
}
