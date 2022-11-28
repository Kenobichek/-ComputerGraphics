#pragma once
#include <vector>

#include "glad.h"

#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 color;
};

class GLRenderSystem
{
public:
    void init();
    void clearDisplay(float r, float g, float b);
    void setViewport(double x, double y, double width, double height);
    void renderTriangleSoup(const std::vector<Vertex>& vertices);
    void setWorldMatrix(const glm::mat4& matrix);
    const glm::mat4& getWorldMatrix();
    void setViewMatrix(const glm::mat4& matrix);
    const glm::mat4& getViewMatrix();
    void setProjectionMatrix(const glm::mat4& matrix);
    const glm::mat4& getProjMatrix();

private:
    glm::mat4 worldMatrix = glm::mat4(1.0f);
    glm::mat4 viewMatrix = glm::mat4(1.0f);
    glm::mat4 projectionMatrix = glm::mat4(1.0f);
};