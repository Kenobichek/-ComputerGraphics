#include "Camera.h"

glm::mat4 Camera::calcViewMatrix() const
{
    return glm::lookAt(eye, target, up);
}

glm::vec3 Camera::calcForward() const
{
    return glm::normalize(target - eye);
}

glm::vec3 Camera::calcRight() const
{
    return glm::normalize(glm::cross(calcForward(), up));
}

double Camera::distanceFromEyeToTarget() const
{
    return glm::length(target - eye);
}

const glm::vec3& Camera::getEye() const
{
    return eye;
}

const glm::vec3& Camera::getTarget() const
{
    return target;
}

void Camera::setFrontView()
{
    double D = distanceFromEyeToTarget();
    setEyeTargetUp(target + glm::vec3{ 0, 0, 1 }, target, { 0, 1, 0 });
    setDistanceToTarget(D);
}

void Camera::setTopView()
{
    glm::vec3 oldTarget = target;
    setFrontView();
    rotate(oldTarget, { 1, 0, 0 }, -(M_PI * 0.5));
}

void Camera::setBottomView()
{
    glm::vec3 oldTarget = target;
    setFrontView();
    rotate(oldTarget, { 1, 0, 0 }, M_PI * 0.5);
}

void Camera::setRearView()
{
    glm::vec3 oldTarget = target;
    setFrontView();
    rotate(oldTarget, { 0, 1, 0 }, M_PI);
}

void Camera::setRightView()
{
    glm::vec3 oldTarget = target;
    setFrontView();
    rotate(oldTarget, { 0, 1, 0 }, (M_PI * 0.5));
}

void Camera::setLeftView()
{
    glm::vec3 oldTarget = target;
    setFrontView();
    rotate(oldTarget, { 0, 1, 0 }, -(M_PI * 0.5));
}


void Camera::setIsoView()
{
}

void Camera::orbit(glm::vec3 a, glm::vec3 b)
{
    glm::vec3 forward = calcForward();
    glm::vec3 right = calcRight();
    float alpha = acos(glm::min(1.0f, glm::dot(a, b)));
    glm::vec3 axis = glm::cross(b, a);
    glm::mat4 orbitMatrix = glm::rotate(glm::mat4(1.0f), (float)alpha, axis);
    eye = glm::vec4(target, 1.0) + orbitMatrix * glm::vec4(eye - target, 1.0f);
    up = orbitMatrix * glm::vec4(up, 1.0f);
}

void Camera::pan(double u, double v)
{
    glm::vec3 offset = calcRight() * (float)u + up * (float)v;
    eye = eye + offset;
    target = target + offset;
}

void Camera::zoom(double factor)
{
}

void Camera::translate(glm::vec3 delta)
{
    eye += delta;
    target += delta;
}

void Camera::setDistanceToTarget(double D)
{
    eye = target - calcForward() * (float)D;
}

void Camera::transform(const glm::mat4& trf)
{
    eye = trf * glm::vec4(eye, 1.0);
    target = trf * glm::vec4(target, 1.0);
    up = trf * glm::vec4(up, 1.0);
}

void Camera::rotate(glm::vec3 point, glm::vec3 axis, double angle)
{
    translate(glm::vec3(0.0, 0.0, 0.0) - point);
    glm::mat4 rot = glm::mat4(1.0f);
    rot = glm::rotate(rot, (float)angle, axis);
    transform(rot);
    translate(point - glm::vec3(0.0, 0.0, 0.0));
}

void Camera::setEyeTargetUp(glm::vec3 newEye, glm::vec3 newTarget, glm::vec3 newUp)
{
    eye = newEye;
    target = newTarget;
    up = glm::rotate(glm::mat4(1.0), 90.0f, glm::cross(calcForward(), newUp)) * glm::vec4(calcForward(), 1.0);
}
