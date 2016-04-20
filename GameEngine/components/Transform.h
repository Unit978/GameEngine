#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Component.h"
#include "../math/Vector3.h"
#include "../math/Matrix4.h"
#include "../math/Quaternion.h"

class Transform : public Component{

public:
    Transform(unsigned entityId = 0,
                const Vector3& position = Vector3(),
                const Quaternion& rotation = Quaternion(),
                const Vector3& scale = Vector3(1, 1, 1));

    // Convert the transform into a matrix
    Matrix4 modelMatrix() const;

    void setParent(Transform* const);

    void update();
    bool hasChanged() const;

    Vector3 position;
    Quaternion rotation;
    Vector3 scale;

    const char* getName() const;

private:
    const Matrix4& getParentMatrix() const;

    Transform* parent;

    // Allow it to be modified inside getParentMatrix() if it needs to be updated.
    mutable Matrix4 parentMatrix;

    Vector3 oldPosition;
    Quaternion oldRotation;
    Vector3 oldScale;
};

#endif // TRANSFORM_H
