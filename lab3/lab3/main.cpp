#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "camera.h"
#include "model.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

Camera camera(-15.0f, 8.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);

glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main()
{
    glfwInit();

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "lab3", NULL, NULL);

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    stbi_set_flip_vertically_on_load(true);

    glEnable(GL_DEPTH_TEST);

    Shader lightShader("../res/light.vs", "../res/light.fs");
    Shader ourShader("../res/texture.vs", "../res/texture.fs");

    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    Model ourModel("../res/nanosuit/nanosuit.obj");

    lightShader.use();
    lightShader.setInt("material.diffuse", 0);
    lightShader.setInt("material.specular", 1);

    glm::mat4 model = glm::mat4(1.0f);
    lightShader.setMat4("model", model);

    model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.03f, 0.03f, 0.03f));
    ourShader.setMat4("model", model);


    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        lightShader.use();
        lightShader.setVec3("light.position", camera.Position);
        lightShader.setVec3("light.direction", camera.Front);
        lightShader.setFloat("light.cutOff", glm::cos(glm::radians(12.5f)));
        lightShader.setFloat("light.outerCutOff", glm::cos(glm::radians(17.5f)));
        lightShader.setVec3("viewPos", camera.Position);
        
        lightShader.setVec3("lightColor", lightColor);
        lightShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
        lightShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
        lightShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
        lightShader.setFloat("light.constant", 1.0f);
        lightShader.setFloat("light.linear", 0.09f);
        lightShader.setFloat("light.quadratic", 0.032f);
        lightShader.setFloat("material.shininess", 32.0f);

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        lightShader.setMat4("projection", projection);
        lightShader.setMat4("view", view);

        ourModel.Draw(ourShader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
        lightColor = glm::vec3(0.0f, 0.0f, 0.0f);
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        lightColor = glm::vec3(1.0f, 0.0f, 0.0f);
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        lightColor = glm::vec3(0.0f, 1.0f, 0.0f);
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
        lightColor = glm::vec3(0.0f, 0.0f, 1.0f);
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
        lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; 

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
