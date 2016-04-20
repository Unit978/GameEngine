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
    T* addComponent(){
        return Engine::componentManager.addComponent<T>(id);
    }

    template<typename T>
    T* getComponent(){
        return Engine::componentManager.getComponent<T>(id);
    }

protected:

private:
    unsigned id;

};

#endif // ENTITY_H
