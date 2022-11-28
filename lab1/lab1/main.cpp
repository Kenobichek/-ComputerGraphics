#include "GLRenderSystem.h"
#include "GLWindow.h"

GLRenderSystem rs;

void createTriangle(std::vector<Vertex>& model, glm::vec3 point1, glm::vec3 point2, glm::vec3 point3, glm::vec3 color)
{
    glm::vec3 normal = glm::normalize(glm::cross(point1 - point2, point3 - point2));
    model.emplace_back(Vertex{ point1, normal, color });
    model.emplace_back(Vertex{ point2, normal, color });
    model.emplace_back(Vertex{ point3, normal, color });
}

std::vector<Vertex> createModel()
{
    std::vector<Vertex> model;
    glm::vec3 color = glm::vec3(0.0f, 0.0f, 1.0f);

    // head
    createTriangle(model, {0, 3, 0}, { 0, 0, 0 }, { 3, 0, 0 }, color);
    createTriangle(model, { 0, 3, 0 }, { 3, 0, 0 }, { 3, 3, 0 }, color);

    // ears
    createTriangle(model, { 3, 3, 0 }, { 6, 3, 0 }, { 8, 4, 0 }, color);
    createTriangle(model, { 3, 3, 0 }, { 8, 4, 0 }, { 5, 4, 0 }, color);

    // body
    createTriangle(model, { 3, 0, 0 }, { 7, -5, 0 }, { 3, -5, 0 }, color);

    // arms
    createTriangle(model, { 3, -4, 0 }, { 3, -6, 0 }, { 2, -5, 0 }, color);

    // legs
    createTriangle(model, { 3, -5, 0 }, { 7, -5, 0 }, { 7, -9, 0 }, color);
    createTriangle(model, { 7, -9, 0 }, { 3, -9, 0 }, { 5, -7, 0 }, color);
    createTriangle(model, { 3, -7, 0 }, { 5, -7, 0 }, { 3, -9, 0 }, color);

    return model;
}

void moveModel(GLRenderSystem& rs, glm::vec3 offset)
{
    glm::mat4 trans = rs.getWorldMatrix();
    trans = glm::translate(trans, offset);
    rs.setWorldMatrix(trans);
}

void onKeyCallback(KeyCode key, Action action, Modifier mods)
{
    const double moveSpeed = 0.1;

    switch (key)
    {
    case KeyCode::W:
        moveModel(rs, glm::vec3(0, moveSpeed, 0));
        break;
    case KeyCode::S:
        moveModel(rs, glm::vec3(0, -moveSpeed, 0));
        break;
    case KeyCode::A:
        moveModel(rs, glm::vec3(-moveSpeed, 0, 0));
        break;
    case KeyCode::D:
        moveModel(rs, glm::vec3(moveSpeed, 0, 0));
        break;
    default:
        break;
    }
}

void renderScene(GLRenderSystem& rs)
{
    rs.renderTriangleSoup(createModel());
}

int main()
{
    glfwInit();

    GLWindow window("myWindow", 480, 640);
    window.setKeyCallback(onKeyCallback);

    rs.init();

    glm::mat4 viewMatrix = glm::lookAt(glm::vec3(4.0f, -2.0f, 25.0f), glm::vec3(4.0f, -2.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    rs.setViewMatrix(viewMatrix);

    glm::mat4 projMatrix = glm::perspective(glm::radians(45.0f), (float)window.getWidth() / (float)window.getHeight(), 0.1f, 100.0f);
    
    rs.setProjectionMatrix(projMatrix);

    while (!glfwWindowShouldClose(window.getGLFWHandle()))
    {
        rs.clearDisplay(1.0f, 0.0f, 0.0f);
        rs.setViewport(0, 0, window.getWidth(), window.getHeight());
        renderScene(rs);
        glfwSwapBuffers(window.getGLFWHandle());
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
