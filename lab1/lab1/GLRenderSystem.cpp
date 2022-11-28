#include "GLRenderSystem.h"

void GLRenderSystem::init()
{
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_COLOR_MATERIAL);
}

void GLRenderSystem::clearDisplay(float r, float g, float b)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(r, g, b, 1.0f);
}

void GLRenderSystem::setViewport(double x, double y, double width, double height)
{
    glViewport((GLint)x, (GLint)y, (GLsizei)width, (GLsizei)height);
}

void GLRenderSystem::renderTriangleSoup(const std::vector<Vertex>& vertices)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMultMatrixf(glm::value_ptr(projectionMatrix));
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(glm::value_ptr(viewMatrix));
    glMultMatrixf(glm::value_ptr(worldMatrix));
    glBegin(GL_TRIANGLES);

    for (const auto& vertex : vertices)
    {
        glNormal3f(vertex.normal.x, vertex.normal.y, vertex.normal.z);
        glColor3f(vertex.color.x, vertex.color.y, vertex.color.z);
        glVertex3f(vertex.position.x, vertex.position.y, vertex.position.z);
    }

    glEnd();
}

void GLRenderSystem::setWorldMatrix(const glm::mat4& matrix)
{
    worldMatrix = matrix;
}

const glm::mat4& GLRenderSystem::getWorldMatrix()
{
    return worldMatrix;
}

void GLRenderSystem::setViewMatrix(const glm::mat4& matrix)
{
    viewMatrix = matrix;
}

const glm::mat4& GLRenderSystem::getViewMatrix()
{
    return viewMatrix;
}

void GLRenderSystem::setProjectionMatrix(const glm::mat4& matrix)
{
    projectionMatrix = matrix;
}

const glm::mat4& GLRenderSystem::getProjMatrix()
{
    return projectionMatrix;
}
