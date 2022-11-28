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
    glfwSetMouseButtonCallback(handle, keyMouseCallback);
    glfwSetCursorPosCallback(handle, keyCursorPosCallback);
    glfwSetScrollCallback(handle, keyScrollCallback);
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

void GLWindow::setCursorPosCallback(const CursorPosCallback& callback)
{
    functionCursorPosCallback = callback;
}

void GLWindow::setMouseCallback(const MouseCallback& callback)
{
    functionMouseCallback = callback;
}

void GLWindow::setScrollCallback(const ScrollCallback& callback)
{
    functionScrollCallback = callback;
}

GLFWwindow* GLWindow::getGLFWHandle()
{
    return handle;
}

void GLWindow::keyCallbackStatic(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    GLWindow* glwwindow = (GLWindow*)glfwGetWindowUserPointer(window);
    glwwindow->functionOnKeyCallback((KeyCode)key, (Action)action, (Modifier)mods);
}

void GLWindow::keyCursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
    GLWindow* glwwindow = (GLWindow*)glfwGetWindowUserPointer(window);
    glwwindow->functionCursorPosCallback(xpos, ypos);
}

void GLWindow::keyMouseCallback(GLFWwindow* window, int button, int action, int mods)
{
    GLWindow* glwwindow = (GLWindow*)glfwGetWindowUserPointer(window);
    double xpos = 0, ypos = 0;
    glfwGetCursorPos(window, &xpos, &ypos);
    glwwindow->functionMouseCallback((ButtonCode)button, (Action)action, (Modifier)mods, xpos, ypos);
}

void GLWindow::keyScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    GLWindow* glwwindow = (GLWindow*)glfwGetWindowUserPointer(window);
    glwwindow->functionScrollCallback(xoffset, yoffset);
}
