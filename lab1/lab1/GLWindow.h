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
    Button_0 = 0,
    //... repeats all buttons codes from the glfw header 
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
    S = 83,
    V = 86,
    W = 87,
    X = 88,
    Z = 90,
    Right = 262,
    Left = 263,
    Down = 264,
    Up = 265,
    Shift = 340,
};

class GLWindow {
public:
    using KeyCallback = std::function<void(KeyCode, Action, Modifier)>;

    GLWindow(const std::string& title, uint32_t width, uint32_t height);
    ~GLWindow();
    uint32_t getWidth();
    uint32_t getHeight();
    void setKeyCallback(const KeyCallback& callback);

    GLFWwindow* getGLFWHandle();

private:
    GLFWwindow* handle = nullptr;
    KeyCallback functionOnKeyCallback;
    static void keyCallbackStatic(GLFWwindow* window, int key, int scancode, int action, int mods);
};