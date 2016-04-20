#ifndef COMPONENT_H
#define COMPONENT_H


class Component
{
public:
    Component(unsigned entityId);
    virtual ~Component();

    unsigned getEntityId() const;
    const char* getName() const;

protected:

    // The entity which this components belongs to.
    // Used to associate groups of components to an entity.
    const unsigned entityId;
};

#endif // COMPONENT_H
