#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <iostream>
#include <cstdlib>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define MIN_SIZE    (0x00)
#define MAX_SIZE    (0x01)
#define SPECIFY     (0x02)


class Window
{
    GLFWwindow *const window;

    GLfloat size[2];

    GLfloat location[2];

    GLfloat scale;

    GLboolean moveStat;

    GLint KeyStatus;

    GLint MouseStatus;

public:
    //  コンストラクタ・・・ウインドウの作成、GLADの初期化
    //  width : ウィンドウの横幅
    //  height : ウインドウの高さ
    //  title : ウインドウの名前
    Window(int width, int height, const char* title, GLenum param, float sscale);

    ~Window();

    explicit operator bool()
    {
        if(KeyStatus == GLFW_RELEASE)
            glfwWaitEvents();
        else   
            glfwPollEvents();

        float blocx, blocy;
        getMousePos(blocx, blocy);
        if( -0.5f * scale / size[0] + location[0] < blocx && 
            blocx < 0.5f * scale / size[0] + location[0] &&
            -0.5f * scale / size[1] + location[1] < blocy && 
            blocy < 0.5f * scale / size[1] + location[1])
        {
            if(MouseStatus != GLFW_RELEASE)
                moveStat = true;
        }
        if(moveStat)
            getMousePos(location[0], location[1]);
        if(MouseStatus == GLFW_RELEASE)
        {
            moveStat = false;
        }

        if(glfwGetKey(window, GLFW_KEY_W))
        {
            location[1] += 0.005f;
        }
        if(glfwGetKey(window, GLFW_KEY_S))
        {
            location[1] -= 0.005f;
        }
        if(glfwGetKey(window, GLFW_KEY_A))
        {
            location[0] -= 0.005f;
        }
        if(glfwGetKey(window, GLFW_KEY_D))
        {
            location[0] += 0.005f;
        }

        return !glfwWindowShouldClose(window);
    }

    //  ウインドウのサイズが変更されたときに呼ばれる関数
    static void resize(GLFWwindow* window, int width, int height)
    {
        int fbwidth,
            fbheight;
        glfwGetFramebufferSize(window, &fbwidth, &fbheight);

        Window *const instance(static_cast<Window*>(glfwGetWindowUserPointer(window)));
        if(instance != nullptr)
        {
            instance->size[0] = fbwidth;
            instance->size[1] = fbheight;
            glViewport(0, 0, fbwidth, fbheight);
            std::cout<<"height : "<<fbheight<<"  width : "<<fbwidth<<std::endl;
        }else{
            std::cerr<<"window instance is NULL"<<std::endl;
        }
    }

    //  キーボードが押されたときに呼ばれる関数
    static void keyBoard(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        Window *const instance(static_cast<Window*>(glfwGetWindowUserPointer(window)));
        if(instance != nullptr)
        {
            //  キーボードの状態を保存
            instance->KeyStatus = action;
        }else{
            std::cerr<<"window instance is NULL"<<std::endl;
        }
    }

    static void button(GLFWwindow* window, int button, int action, int mods)
    {
        Window *const instance(static_cast<Window *>(glfwGetWindowUserPointer(window)));
        if(instance != nullptr)
        {
            instance->MouseStatus = action;
        }else{
            std::cerr<<"window instance is NULL"<<std::endl;
        }
    }

    virtual void getMousePos(float &x, float &y) const
    {
            double xb, yb;
            glfwGetCursorPos(window, &xb, &yb);
            x = ((static_cast<float>(xb) / size[0]) * 2.0f - 1.0f) * 2.0f;
            y = (1.0f - (static_cast<float>(yb) / size[1]) * 2.0f) * 2.0f;
    }

    void swapBuffers() const
    {
        glfwSwapBuffers(window);
    }

    void clearColor() const
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    const GLfloat *(getSize() const)  { return size; }

    GLfloat getScale() const { return scale; }

    const GLfloat *(getLocation() const) { return location; }
};

#endif //   WINDOW_H_