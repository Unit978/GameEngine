#include "Component.h"

Component::Component(unsigned entityId) :
    entityId(entityId)
{
    //ctor
}

Component::~Component()
{
    //dtor
}

unsigned Component::getEntityId() const{
    return entityId;
}

const char* Component::getName() const{
    return "COMPONENT";
}
