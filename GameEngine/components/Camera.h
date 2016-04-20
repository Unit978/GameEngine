#ifndef CAMERA_H
#define CAMERA_H

#include "../math/Vector3.h"
#include "../math/Quaternion.h"
#include "../math/Matrix4.h"

#include "Transform.h"
#include "MeasurementUnits.h"

class Camera{

public:

    // Creates an internal perspective matrix based on the field of view, aspect ratio,
    // the minimum distance, and the maximum distance of view.
    // The field of view is the vertical angle (in radians) which the camera sees into the world. Acts as zooming.
    // The aspect ratio is the ratio between the width and height of our target (screen)
    // rectangular area to project on.
    Camera(float, float, float, float);

    // Creates an orthogonal camera.
    // Takes in the width and height of the screen
    Camera(float, float);

    enum Orientation {FORWARD, BACK, LEFT, RIGHT, UP, DOWN};
    enum ViewType {PERSPECTIVE, ORTHO};

    // Returns the camera's view projection of the world
    Matrix4 getViewProjection() const;

    // Holds position, rotation, and scale data of the camera.
    Transform transform;

    void move(Orientation, float);
    void rotate(const Radians& yaw, const Radians& pitch, const Radians& roll);
    void rotate(const Degrees& yaw, const Degrees& pitch, const Degrees& roll);
    void zoom(float);
    bool isInsideCameraView(const Vector3&) const;

    const Vector3& getLookAt() const;
    const Vector3& getUp() const;

    float getWidth() const;
    float getHeight() const;

    const enum ViewType& getViewType() const;

private:

    ViewType cameraView;

    bool isInsideFrustum(const Vector3&) const;
    bool isInsideOrthoPrism(const Vector3&) const;

    // The upwards orientation of the camera
    Vector3 up;

    // The "look at" orientation - the orientation where the camera faces
    Vector3 lookAt;

    // The type of camera projection which can be perspective or orthogonal
    Matrix4 projection;

    // The default width and height of the camera view port rectangle.
    // TanFOV is the tangent of the field of view angle.
    float defaultWidth, defaultHeight, defaultFOV, defaultTanFOV;

    // These are the current scaled values of the camera (applied when camera zooms).
    float width, height, tanFOV;

    float aspectRatio, zNear, zFar;

    // have a variable which is texture output.
    // The camera will output to this texture instead
    // of the whole screen.
};

#endif // CAMERA_H
