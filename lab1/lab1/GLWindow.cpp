#include "GLWindow.h"

GLWindow::GLWindow(const std::string& title, uint32_t width, uint32_t height)
{
    handle = glfwCreateWindow(width, height, title.data(), NULL, NULL);

    glfwMakeContextCurrent(handle);
    static bool initGLAD = false;
    if (!initGLAD)
    {
        initGLAD = true;
        gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    }

    glfwSetWindowUserPointer(handle, this);
    glfwSetKeyCallback(handle, keyCallbackStatic);
}

GLWindow::~GLWindow()
{
}

uint32_t GLWindow::getWidth()
{
    int width = 0;
    glfwGetWindowSize(handle, &width, nullptr);
    return width;
}

uint32_t GLWindow::getHeight()
{
    int height = 0;
    glfwGetWindowSize(handle, nullptr, &height);
    return height;
}

void GLWindow::setKeyCallback(const KeyCallback& callback)
{
    functionOnKeyCallback = callback;
}

GLFWwindow* GLWindow::getGLFWHandle()
{
    return handle;
}

void GLWindow::keyCallbackStatic(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    GLWindow* glWindow = (GLWindow*)glfwGetWindowUserPointer(window);
    glWindow->functionOnKeyCallback((KeyCode)key, (Action)action, (Modifier)mods);
}
