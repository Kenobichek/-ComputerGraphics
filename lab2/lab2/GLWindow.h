#pragma once
#include "glad.h"

#include <glfw\glfw3.h>
#include <functional>
#include <string>

enum class Modifier
{
    NoModifier = 0,
    Shift = 1,
    Control = 2,
    Alt = 4,
    Super = 8,
};

enum class Action
{
    Release = 0,
    Press = 1,
    Repeat = 2,
};

enum class ButtonCode {
    ButtonLeft = 0,
    ButtonRight = 1
};

enum class KeyCode {
    UNKNOWN = -1,
    Space = 32,
    A = 65,
    B = 66,
    C = 67,
    D = 68,
    F = 70,
    G = 71,
    H = 72,
    J = 74,
    N = 78,
    O = 79,
    P = 80,
    S = 83,
    V = 86,
    W = 87,
    X = 88,
    Z = 90,
    Right = 262,
    Left = 263,
    Down = 264,
    Up = 265,
    F1 = 290,
    F2 = 291,
    F3 = 292,
    F4 = 293,
    F5 = 294,
    F6 = 295,
    F7 = 296,
    F8 = 297,
    Shift = 340,
};

class GLWindow {
public:
    using KeyCallback = std::function<void(KeyCode, Action, Modifier)>;
    using CursorPosCallback = std::function<void(double, double)>;
    using MouseCallback = std::function<void(ButtonCode, Action, Modifier, double, double)>;
    using ScrollCallback = std::function<void(double, double)>;

    GLWindow(const std::string& title, uint32_t width, uint32_t height);
    ~GLWindow();
    uint32_t getWidth();
    uint32_t getHeight();
    void setKeyCallback(const KeyCallback& callback);
    void setCursorPosCallback(const CursorPosCallback& callback);
    void setMouseCallback(const MouseCallback& callback);
    void setScrollCallback(const ScrollCallback& callback);
    GLFWwindow* getGLFWHandle();

private:
    GLFWwindow* handle = nullptr;
    KeyCallback functionOnKeyCallback;
    CursorPosCallback functionCursorPosCallback;
    MouseCallback functionMouseCallback;
    ScrollCallback functionScrollCallback;

    static void keyCallbackStatic(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void keyCursorPosCallback(GLFWwindow* window, double xpos, double ypos);
    static void keyMouseCallback(GLFWwindow* window, int button, int action, int mods);
    static void keyScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
};