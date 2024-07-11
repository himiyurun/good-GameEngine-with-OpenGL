#ifndef _INPUT_H_
#define _INPUT_H_
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Input
{
    GLFWwindow* const* window;

    GLint KeyStat;

    GLint MouseStat;

    GLfloat MousePos[2];

public:

    Input(GLFWwindow* const* window)
        : window(window)
        , KeyStat(GLFW_RELEASE)
        , MouseStat(GLFW_RELEASE)
    {}

    virtual void swapInput() const
    {
        if(KeyStat == GLFW_RELEASE)
            glfwWaitEvents();
        else
            glfwPollEvents();
    }

    GLboolean getKey(int key) const { return glfwGetKey(*window, key); }

    virtual void setMousePos(float size[2])
    {
        double xb, yb;
        glfwGetCursorPos(*window, &xb, &yb);
        MousePos[0] = ((static_cast<float>(xb) / size[0]) * 2.0f - 1.0f) * 2.0f;
        MousePos[1] = (1.0f - (static_cast<float>(yb) / size[1]) * 2.0f) * 2.0f;
    }

    virtual void setKeyStat(int action)
    {
        KeyStat = action;
    }

    virtual void setMouseStat(int action)
    {
        MouseStat = action;
    }

    GLint getKeystat() const { return KeyStat; }

    GLint getMouseStat() const { return MouseStat; }

    const GLfloat *(getMousePos() const) { return MousePos; }
};

#endif // _INPUT_H_