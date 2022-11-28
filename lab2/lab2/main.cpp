#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>
#include <functional>

#include "GLWindow.h"
#include "GLRenderSystem.h"
#include "Viewport.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

GLRenderSystem rs;
Viewport viewport;

void createTriangle(std::vector<Vertex>& model, glm::vec3 point1, glm::vec3 point2, glm::vec3 point3, glm::vec3 color)
{
    glm::vec3 normal = glm::normalize(glm::cross(point1 - point2, point3 - point2));
    model.emplace_back(Vertex{ point1, normal, color });
    model.emplace_back(Vertex{ point2, normal, color });
    model.emplace_back(Vertex{ point3, normal, color });
}

std::vector<Vertex> createFun()
{
    //Z = sin(y) * sqrt(x)
    std::vector<std::vector<glm::vec3>> points;
    std::vector<Vertex> fun;
    double step = 0.5;
    double range = 10;
    for (double x = -range; x <= range; x += step)
    {
        std::vector<glm::vec3> rowPoints;
        for (double y = -range; y < range; y += step)
        {
            double z = sin(y) + sqrt(abs(x));
            rowPoints.push_back(glm::vec3(x, y, z));
        }
        points.push_back(rowPoints);
    }

    for (int i = 0; i < points.size() - 1; i++)
    {
        for (int j = 0; j < points[i].size() - 1; j++)
        {
            fun.push_back({ points[i][j], glm::vec3(0, 0, 1), glm::vec3(1, 0.5, 0.9) });
            fun.push_back({ points[i][j + 1], glm::vec3(0, 0, 1), glm::vec3(1, 0.5, 0.9) });
            fun.push_back({ points[i][j + 1], glm::vec3(0, 0, 1), glm::vec3(1, 0.5, 0.9) });
            fun.push_back({ points[i + 1][j], glm::vec3(0, 0, 1), glm::vec3(1, 0.5, 0.9) });
            fun.push_back({ points[i + 1][j], glm::vec3(0, 0, 1), glm::vec3(1, 0.5, 0.9) });
            fun.push_back({ points[i][j], glm::vec3(0, 0, 1), glm::vec3(1, 0.5, 0.9) });


            fun.push_back({ points[i + 1][j + 1], glm::vec3(0, 0, 1), glm::vec3(1, 0.5, 0.9) });
            fun.push_back({ points[i + 1][j], glm::vec3(0, 0, 1), glm::vec3(1, 0.5, 0.9) });
            fun.push_back({ points[i + 1][j], glm::vec3(0, 0, 1), glm::vec3(1, 0.5, 0.9) });
            fun.push_back({ points[i][j + 1], glm::vec3(0, 0, 1), glm::vec3(1, 0.5, 0.9) });
            fun.push_back({ points[i][j + 1], glm::vec3(0, 0, 1), glm::vec3(1, 0.5, 0.9) });
            fun.push_back({ points[i + 1][j + 1], glm::vec3(0, 0, 1), glm::vec3(1, 0.5, 0.9) });
        }
    }
    return fun;
}

std::vector<Vertex> createOctahedron(GLRenderSystem& rs, const float length, const float shiftFromTheCenter, const glm::vec3& color)
{
    float pointPosition = length / 2;

    glm::vec3 A = glm::vec3(0, pointPosition, 0 + shiftFromTheCenter);
    glm::vec3 B = glm::vec3(0, -pointPosition, 0 + shiftFromTheCenter);

    glm::vec3 C = glm::vec3(0, 0, pointPosition + shiftFromTheCenter);
    glm::vec3 D = glm::vec3(0, 0, -pointPosition + shiftFromTheCenter);

    glm::vec3 E = glm::vec3(-pointPosition, 0, 0 + shiftFromTheCenter);
    glm::vec3 F = glm::vec3(pointPosition, 0, 0 + shiftFromTheCenter);

    std::vector<Vertex> octahedron;

    // TOP
    createTriangle(octahedron, A, E, C, glm::vec3(1, 0.5, 1));
    createTriangle(octahedron, A, C, F, glm::vec3(0.5, 0.5, 0));
    createTriangle(octahedron, A, F, D, glm::vec3(0.5, 0.5, 0.5));
    createTriangle(octahedron, A, D, E, glm::vec3(1, 1, 1));

    // BOTTOM
    createTriangle(octahedron, B, E, C, glm::vec3(1, 1, 1));
    createTriangle(octahedron, B, C, F, glm::vec3(0.5, 0.5, 0.5));
    createTriangle(octahedron, B, F, D, glm::vec3(1, 0.5, 1));
    createTriangle(octahedron, B, D, E, glm::vec3(0.5, 0.5, 0));

    return octahedron;
}

glm::vec3 getPosition(const double& radius, const double& posVerticalSegment,
    const double& posHorizontalSegment, const double& slicesStep, const double& ringsStep)
{
    double slicesAngle = M_PI_2 - posVerticalSegment * slicesStep;
    double ringsAngle = posHorizontalSegment * ringsStep;

    double x = radius * cos(slicesAngle) * cos(ringsAngle);
    double y = radius * cos(slicesAngle) * sin(ringsAngle);
    double z = radius * sin(slicesAngle);

    return { x, y, z };
}

std::vector<Vertex> createSphere(GLRenderSystem& rs, const double radius, const float shiftFromTheCenter,
    const unsigned int sliceCount, const unsigned int ringCount, const glm::vec3& color)
{
    std::vector<glm::vec3> vertices;

    double slicesStep = M_PI / sliceCount;
    double ringsStep = 2 * M_PI / ringCount;

    for (unsigned int i = 0; i <= sliceCount; i++)
    {
        for (unsigned int j = 0; j <= ringCount; j++)
        {
            glm::vec3 vertex = getPosition(radius, i, j, slicesStep, ringsStep);
            vertices.emplace_back(glm::vec3{ vertex.x, vertex.y, vertex.z + shiftFromTheCenter });
        }
    }

    std::vector<Vertex> sphere;
    // We have to triangulate each sector of the mesh formed by the intersections of "parallels" and "meridians" on the sphere

    // To do it devide                 A ****** B      A ****** B       A * 
    // rectangle ABCD                    ******    ->       ***    and    ***                
    // on two trianlge ABC and BCD     D ****** C      D      * C       D ****** C

    for (int i = 0; i <= vertices.size() - (ringCount + sliceCount) + (sliceCount - 2); i++)
    {
        int B = i + 1;
        int D = i + ringCount;
        int C = i + ringCount + 1;

        createTriangle(sphere, vertices[i], vertices[C], vertices[B], color);
        createTriangle(sphere, vertices[i], vertices[D], vertices[C], color);
    }
    return sphere;
}

void moveCamera(Camera& camera, glm::vec3 offset)
{
    camera.translate(offset);
}

void moveModel(GLRenderSystem& rs, glm::vec3 offset)
{
    glm::mat4 trans = rs.getWorldMatrix();
    trans = glm::translate(trans, offset);
    rs.setWorldMatrix(trans);
}

void renderScene(GLRenderSystem& rs)
{
    rs.renderTriangleSoup(createOctahedron(rs, 6, -10, glm::vec3(1, 0, 0)));
    rs.renderLines(createSphere(rs, 3, 10, 15, 20, glm::vec3(1, 1, 0)));
    rs.renderLines(createFun());
}

void onKeyCallback(KeyCode key, Action action, Modifier mods)
{
    const double moveCubeSpeed = 0.1;
    const double moveCameraSpeed = 1.0;

    switch (key)
    {
        // Movement model
    case KeyCode::Up:
        moveModel(rs, glm::vec3(0, moveCubeSpeed, 0));
        break;
    case KeyCode::Down:
        moveModel(rs, glm::vec3(0, -moveCubeSpeed, 0));
        break;
    case KeyCode::Right:
        moveModel(rs, glm::vec3(-moveCubeSpeed, 0, 0));
        break;
    case KeyCode::Left:
        moveModel(rs, glm::vec3(moveCubeSpeed, 0, 0));
        break;
    case KeyCode::W:
        moveCamera(viewport.getCamera(), glm::vec3(0, moveCameraSpeed, 0));
        break;
    case KeyCode::S:
        moveCamera(viewport.getCamera(), glm::vec3(0, -moveCameraSpeed, 0));
        break;
    case KeyCode::A:
        moveCamera(viewport.getCamera(), glm::vec3(moveCameraSpeed, 0, 0));
        break;
    case KeyCode::D:
        moveCamera(viewport.getCamera(), glm::vec3(-moveCameraSpeed, 0, 0));
        break;
    case KeyCode::F1:
        viewport.getCamera().setFrontView();
        break;
    case KeyCode::F2:
        viewport.getCamera().setTopView();
        break;
    case KeyCode::F3:
        viewport.getCamera().setRearView();
        break;
    case KeyCode::F4:
        viewport.getCamera().setRightView();
        break;
    case KeyCode::F5:
        viewport.getCamera().setLeftView();
        break;
    case KeyCode::F6:
        viewport.getCamera().setBottomView();
        break;
    case KeyCode::F7:
        viewport.getCamera().setIsoView();
        break;
    default:
        break;
    }

    if (action != Action::Release) return;

    switch (key)
    {
    case KeyCode::P:
        viewport.setFOV(60);
        break;
    case KeyCode::O:
        viewport.setFOV(20);
        break;
    default:
        break;
    }

}

void keyScrollCallback(double xoffset, double yoffset)
{
    moveModel(rs, glm::vec3(0, 0, yoffset));
}

glm::vec3 a{ 0, 0, 0 }, b{ 0, 0, 0 };

void mouseCallback(ButtonCode button, Action action, Modifier mods, double xpos, double ypos)
{
    if (button == ButtonCode::ButtonRight && action == Action::Press)
    {
        viewport.getCamera().modeCamera = ModeCamera::ButtonRight;
        float screenSizeRatio = viewport.getWidth() / viewport.getHeight();

        a.x = (2 * screenSizeRatio * xpos) / viewport.getWidth() - screenSizeRatio;
        a.y = 1 - ((2 * ypos) / viewport.getHeight());
        auto vecLength = a.x * a.x + a.y * a.y;
        if (glm::length(a) > 1.0)
        {
            a = glm::normalize(a);
        }
        else
        {
            a.z = sqrt(1.0 - pow(a.x, 2) - pow(a.y, 2));
        }
    }
    else if (button == ButtonCode::ButtonLeft && action == Action::Press)
    {
        viewport.getCamera().modeCamera = ModeCamera::ButtonLeft;
    }
    else if (action == Action::Release)
    {
        viewport.getCamera().modeCamera = ModeCamera::NotSelected;
    }
}

void cursorPosCallback(double xpos, double ypos)
{
    static double u0 = viewport.getWidth() / 2, v0 = viewport.getHeight() / 2;
    if (viewport.getCamera().modeCamera != ModeCamera::NotSelected)
    {
        if (viewport.getCamera().modeCamera == ModeCamera::ButtonRight)
        {
            float screenSizeRatio = viewport.getWidth() / viewport.getHeight();

            b.x = (2 * screenSizeRatio * xpos) / viewport.getWidth() - screenSizeRatio;
            b.y = 1 - ((2 * ypos) / viewport.getHeight());

            auto vecLength = b.x * b.x + b.y * b.y;
            if (glm::length(b) > 1.0)
            {
                b = glm::normalize(b);
            }
            else
            {
                b.z = sqrt(1.0 - pow(b.x, 2) - pow(b.y, 2));
            }
            if (a != b)
                viewport.getCamera().orbit(a, b);
            a = b;
        }
        else
        {
            float speedCamera = 0.05;
            double dU = u0 - xpos;
            double dV = ypos - v0;
            viewport.getCamera().pan(dU * speedCamera, dV * speedCamera);
        }
    }
    u0 = xpos;
    v0 = ypos;
}

int main()
{
    glfwInit();

    GLWindow window("myWindow", 640, 480);

    viewport.setViewportSize(640, 480);
    viewport.setFOV(60);
    viewport.setZNear(0.1);
    viewport.setZFar(500);

    window.setKeyCallback(onKeyCallback);
    window.setCursorPosCallback(cursorPosCallback);
    window.setMouseCallback(mouseCallback);
    window.setScrollCallback(keyScrollCallback);

    rs.init();

    while (!glfwWindowShouldClose(window.getGLFWHandle()))
    {
        rs.setViewport(0, 0, window.getWidth(), window.getHeight());
        rs.clearDisplay(0.0f, 0.0f, 0.0f);
        rs.setViewMatrix(viewport.getCamera().calcViewMatrix());
        rs.setProjectionMatrix(viewport.calcProjectionMatrix());
        renderScene(rs);
        glfwSwapBuffers(window.getGLFWHandle());
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
