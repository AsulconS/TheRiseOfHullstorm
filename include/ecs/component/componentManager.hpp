#ifndef ECS_COMPONENT_MANAGER_H
#define ECS_COMPONENT_MANAGER_H

#include <iostream>

#include "system/common.hpp"
#include "dataStructures.hpp"

#include "ecs/component/component.hpp"

/* Component Manger:
 * The Component Manager handles how to treat
 * the data into the component containers.
 * 
 * It doesn't has to know the specific type
 * of the component due to it's a Generic Templated
 * class, so C is the Component Type
 */
class ComponentManager
{
public:
    static uint32 registerComponentType();

    template <typename C>
    static C* createComponent(Entity* entity);

    class Experimental
    {
        template <typename C>
        static C* registerComponent(C* component, Entity* entity);

        static void clearMemory();
    };

    template <typename C>
    static bool deleteComponent(Entity* entity);

    template <typename C>
    static List<BaseComponent*>& getComponentMemory();

    static void outLog();

private:
    static uint32 componentID;
    static uint32 globalComponentsCount;
    static uint32 destroyedGlobalComponentsCount;
    static Vector<List<BaseComponent*>> componentMemory;
    static List<BaseComponent*>::iterator componentIt;
};

#endif // ECS_COMPONENT_MANAGER_H
