#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include <iostream>
#include <unordered_map>
#include <typeindex>

#include "Component.h"

using std::unordered_multimap;
using std::unordered_map;

class ComponentManager
{
public:
    ComponentManager();
    ~ComponentManager();

    template<typename T>
    T* addComponent(unsigned entityId);

    template<typename T>
    T* getComponent(unsigned entityId) const;

private:

    unsigned getComponentTypeId(const std::type_index&) const;
    uint64_t getMaskKey(unsigned entityId, unsigned componentTypeId) const;

    // Stores the integer representation of the component type.
    // Used to add and query for a component.
    mutable unordered_map<std::type_index, unsigned> componentTypeIds;

    // Stores all the components.
    // It also associates an entity to the component.
    unordered_multimap <uint64_t, Component*> components;
};

template<typename T>
T* ComponentManager::addComponent(unsigned entityId){

    // Create a new component and a mask to associate the entity and component type.
    T* newComponent = new T(entityId);
    unsigned componentTypeId = getComponentTypeId(typeid(T));
    uint64_t mask = getMaskKey(entityId, componentTypeId);

    // Insert the new component into the map.
    std::pair<uint64_t, Component*> pair(mask, newComponent);
    components.insert(pair);
    return newComponent;
}

template <typename T>
T* ComponentManager::getComponent(unsigned entityId) const{

    unsigned componentTypeId = getComponentTypeId(typeid(T));
    uint64_t mask = getMaskKey(entityId, componentTypeId);

    // Find the mask key in the dictionary and return the component if it exists.
    auto mapItr = components.find(mask);
    if (mapItr != components.end()){
        return static_cast<T*>(mapItr->second);
    }

    // Not found
    else{
        return nullptr;
    }
}

#endif // COMPONENTMANAGER_H
