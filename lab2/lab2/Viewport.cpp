#include "Viewport.h"

glm::mat4 Viewport::calcProjectionMatrix()
{
    return glm::perspective(glm::radians((float)FOV), ((float)ViewportSizeWidth / ViewportSizeHeight), (float)ZNear, (float)ZFar);
}

void Viewport::setViewportSize(uint32_t inWidth, uint32_t inHeight)
{
    ViewportSizeWidth = inWidth;
    ViewportSizeHeight = inHeight;
}

void Viewport::setFOV(double inFOV)
{
    FOV = inFOV;
}

void Viewport::setZNear(double inZNear)
{
    ZNear = ZNear;
}

void Viewport::setZFar(double inZFar)
{
    ZFar = inZFar;
}

void Viewport::setParallelProjection(bool use)
{
    parallelProjection = use;
}

double Viewport::getZNear()
{
    return ZNear;
}

double Viewport::getZFar()
{
    return ZFar;
}

double Viewport::getFov()
{
    return FOV;
}

double Viewport::getWidth()
{
    return ViewportSizeWidth;
}

double Viewport::getHeight()
{
    return ViewportSizeHeight;
}

bool Viewport::isParallelProjection()
{
    return parallelProjection;
}

ray Viewport::calcCursorRay(double x, double y)
{
    glm::vec3 a = glm::unProject(glm::vec3(x, y, -1.0), getCamera().calcViewMatrix(), calcProjectionMatrix(), glm::vec4(0.0f, 0.0f, getWidth(), getHeight()));
    glm::vec3 b = glm::unProject(glm::vec3(x, y, 1.0), getCamera().calcViewMatrix(), calcProjectionMatrix(), glm::vec4(0.0f, 0.0f, getWidth(), getHeight()));
    ray cursorRay{ a, normalize(b - a) };
    return cursorRay;
}

double Viewport::calcTargetPlaneWidth()
{
    return calcTargetPlaneHeight() * calcAspectRatio();
}

double Viewport::calcTargetPlaneHeight()
{
    return 2.0 * camera.distanceFromEyeToTarget() * tan(glm::radians(FOV / 2.0));
}

double Viewport::calcAspectRatio()
{
    return 0;
}

Camera& Viewport::getCamera()
{
    return camera;
}

const Camera& Viewport::getCamera() const
{
    return camera;
}
