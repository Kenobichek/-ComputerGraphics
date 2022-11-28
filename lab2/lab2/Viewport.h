#pragma once

#include "Camera.h"

struct ray
{
    glm::vec3 orig;
    glm::vec3 dir{ 0,0,1 };
};

class Viewport {
public:
    glm::mat4 calcProjectionMatrix();
    void setViewportSize(uint32_t inWidth, uint32_t inHeight);
    void setFOV(double inFOV);
    void setZNear(double inZNear);
    void setZFar(double inZFar);
    void setParallelProjection(bool use);
    double getZNear();                // 0.01 by default 
    double getZFar();                 // 500 by default 
    double getFov();                  // 60 in degrees by default 
    double getWidth();                // 1 by default 
    double getHeight();               // 1 by default 
    bool isParallelProjection();      // false by default 

    ray calcCursorRay(double x, double y);
    double calcTargetPlaneWidth();
    double calcTargetPlaneHeight();
    double calcAspectRatio();

    Camera& getCamera();
    const Camera& getCamera() const;

private:
    uint32_t ViewportSizeWidth = 1;
    uint32_t ViewportSizeHeight = 1;
    double FOV = 60;
    double ZNear = 0.01;
    double ZFar = 60;
    bool parallelProjection = false;
    Camera camera;
};