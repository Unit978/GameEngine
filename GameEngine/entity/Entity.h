#ifndef ENTITY_H
#define ENTITY_H

#include "../core/Engine.h"
#include "../components/Component.h"

class Entity
{

public:
    Entity();

    unsigned getId() const;

    template<typename T>
    T* addComponent();

    template<typename T>
    T* getComponent();

protected:

private:
    unsigned id;

};

template<typename T>
T* Entity::addComponent(){
    return Engine::componentManager.addComponent<T>(id);
}

template<typename T>
T* Entity::getComponent(){
    return Engine::componentManager.getComponent<T>(id);
}

#endif // ENTITY_H
