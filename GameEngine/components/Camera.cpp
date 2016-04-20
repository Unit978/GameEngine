#include "Camera.h"
#include <cmath>

#include <iostream>
using namespace std;

Camera::Camera(float fieldOfView, float aspectRatio, float zNear, float zFar){

    projection = Matrix4::perspective(fieldOfView, aspectRatio, zNear, zFar);

    // Have up be defined by the y-axis
    up = Vector3(0, 1, 0);

    // have the camera look towards the z axis
    lookAt = Vector3(0, 0, 1);

    defaultFOV = fieldOfView;
    defaultTanFOV = tanFOV = tanf(0.5f * fieldOfView);
    defaultHeight = 2 * tanFOV * zNear;
    defaultWidth = width = aspectRatio * height;

    this->zNear = zNear;
    this->zFar = zFar;
    this->aspectRatio = aspectRatio;

    cameraView = PERSPECTIVE;
}

Camera::Camera(float width, float height){
    projection = Matrix4::ortho(0, width, 0, height, -1, 1);

    up = Vector3(0, 1, 0);
    lookAt = Vector3(0, 0, 1);

    zNear = -1;
    zFar = 1;

    this->width = defaultWidth = width;
    this->height = defaultHeight = height;

    aspectRatio = width/height;

    // There is no view angle with orthographic projection
    tanFOV = defaultTanFOV = defaultFOV = 0;

    cameraView = ORTHO;
}

Matrix4 Camera::getViewProjection() const{

    // Negate the position values
    Vector3 position = transform.position * -1;

    // Create the translation with the negated position values
    Matrix4 translation = Matrix4::translation(Vector3(position.x, position.y, position.z));

    // Orhtographic view projections
    if (cameraView == ORTHO)
        return projection * Matrix4::lookAt(transform.position, transform.position + lookAt, up) * translation;

    // Negations are done in order to create the illusion of camera movement.
    // Example: If the camera moves right, everything appears to move left.
    // If the camera rotates left, everything appears to rotate right.
    Matrix4 rotation = transform.rotation.getConjugate().toMatrix();

    // Create the perspective view projection matrix, also rotate then translate so
    // the camera can free look in place.
    return projection * Matrix4::lookAt(transform.position, transform.position + lookAt, up) * rotation * translation;
}

void Camera::move(Orientation o, float speed){
    switch (o){
        case FORWARD:   transform.position -= transform.rotation.getForward()   * speed; break;
        case BACK:      transform.position -= transform.rotation.getBack()      * speed; break;
        case LEFT:      transform.position += transform.rotation.getLeft()      * speed; break;
        case RIGHT:     transform.position += transform.rotation.getRight()     * speed; break;
        case UP:        transform.position += transform.rotation.getUp()        * speed; break;
        case DOWN:      transform.position += transform.rotation.getDown()      * speed; break;
    }
}

// Free look camera behavior
void Camera::rotate(const Radians& yaw, const Radians& pitch, const Radians& roll){

    // Yaw. Rotate along the global Y axis
    transform.rotation.rotate(yaw, up);

    // Pitch. Rotate along the horizontal axis of the camera
    Vector3 haxis = transform.rotation.getRight();
    transform.rotation.rotate(pitch, haxis);

    // Roll. Rotate along the forward vector of the camera
    transform.rotation.rotate(roll, transform.rotation.getForward());
}

void Camera::zoom(float scale){

    if (cameraView == ORTHO){
        projection = Matrix4::ortho(0, defaultWidth*scale, 0, defaultHeight*scale, -1, 1);
        width = defaultWidth * scale;
        height = defaultHeight * scale;
    }
    else if (cameraView == PERSPECTIVE){
        projection = Matrix4::perspective(defaultFOV*scale, aspectRatio, zNear, zFar);
        tanFOV = defaultFOV * scale;
    }
}

bool Camera::isInsideCameraView(const Vector3& point) const{
    if (cameraView == PERSPECTIVE)
        return isInsideFrustum(point);

    return isInsideOrthoPrism(point);
}

bool Camera::isInsideFrustum(const Vector3& point) const{

    // The view angle must be a positive real value.
    if (tanFOV <= 0)
        return false;

    // NOTE: COORDINATE SYSTEM USES RIGHT HAND - POSITIVE Z AXIS POINTS OUT THE SCREEN
    // Obtain vector from camera position to the point
    Vector3 toPoint = point - this->transform.position;

    // Get the z value of the projection of toPoint onto the camera's forward vector
    float zProj = toPoint.dot(this->transform.rotation.getForward());

    // Test the z value between the near and far planes.
    // Return false if it is outside those planes.
    if (zProj > -zNear || zProj < -zFar)
        return false;

    // Get the y value of the projection of toPoint onto the camera's up vector
    float yProj = toPoint.dot(this->transform.rotation.getUp());

    // Get the height of the frustrum at the projected point
    float fheight = 2 * -zProj * this->tanFOV;

    // Test if the Y coordinate is between the upper and lower planes.
    // Return false if it is outside those planes.
    if (yProj < -fheight/2 || yProj > fheight/2)
        return false;

    // Get the x value of the projection of toPoint onto the camera's right vector
    float xProj = toPoint.dot(this->transform.rotation.getRight());

    // Get the width of the frustrum at the projected point
    float fwidth = this->aspectRatio * fheight;

    // Test if the X coordinate is between the left and right planes.
    // Return false if it is outside those planes.
    if (xProj < -fwidth/2 || xProj > fwidth/2)
        return false;

    // Point is inside the frustrum
    return true;
}

bool Camera::isInsideOrthoPrism(const Vector3& point) const{

    float camx = transform.position.x;
    float camy = transform.position.y;

    if (point.x < camx || point.x > camx + width )
        return false;

    if (point.y < camy|| point.y > camy + height)
        return false;

    if (point.z > -zNear || point.z < -zFar)
        return false;

    return true;
}

const Vector3& Camera::getLookAt() const{
    return lookAt;
}

const Vector3& Camera::getUp() const{
    return up;
}

float Camera::getWidth() const{
    return width;
}

float Camera::getHeight() const{
    return height;
}

const Camera::ViewType& Camera::getViewType() const{
    return cameraView;
}
