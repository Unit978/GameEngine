#include "Transform.h"
#include "MeasurementUnits.h"

Transform::Transform(unsigned entityId, const Vector3& position, const Quaternion& rotation, const Vector3& scale) :
    Component(entityId), position(position), rotation(rotation), scale(scale)
{
    oldPosition = position;
    oldScale = scale;
    oldRotation = rotation;
    parent = nullptr;
}

Matrix4 Transform::modelMatrix() const{

    Matrix4 posMat = Matrix4::translation(position);
    Matrix4 rotMat = rotation.toMatrix();
    Matrix4 scaleMat = Matrix4::scale(scale);

    // Have the transform relative to the parent
    return getParentMatrix() * posMat * rotMat * scaleMat;
}

void Transform::setParent(Transform* const parent){
    this->parent = parent;

    // Update the parent matrix
    if (parent)
        parentMatrix = parent->modelMatrix();
}

void Transform::update(){
    oldPosition = position;
    oldScale = scale;
    oldRotation = rotation;
}

bool Transform::hasChanged() const{

    if (parent && parent->hasChanged())
        return true;

    if (position != oldPosition)
        return true;

    if (scale != oldScale)
        return true;

    if (rotation != oldRotation)
        return true;

    return false;
}

const Matrix4& Transform::getParentMatrix() const{
    if (parent && parent->hasChanged())
        parentMatrix = parent->modelMatrix();
    return parentMatrix;
}

const char* Transform::getName() const{
    return "TRANSFORM";
}

