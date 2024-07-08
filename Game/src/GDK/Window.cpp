#include "Window.h"

Window::Window(int width, int height, const char* title, GLenum param, float sscale = 0.0f)
    : window(glfwCreateWindow(width, height, title, NULL, NULL))
    , KeyStatus(GLFW_RELEASE)
    , MouseStatus(GLFW_RELEASE)
    , moveStat(false)
    {
        if(window == NULL)
    {
        std::cerr<<"window is NULL"<<std::endl;
        exit(1);
    }

    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        std::cerr<<"Can't Load GLAD"<<std::endl;
        exit(1);
    }
    
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

    glfwSwapInterval(1);

    glfwSetWindowUserPointer(window, this);

    glfwSetWindowSizeCallback(window, resize);

    glfwSetKeyCallback(window, keyBoard);

    glfwSetMouseButtonCallback(window, button);

    resize(window, width, height);

    location[0] = 0.0f;
    location[1] = 0.0f;

    if(param != SPECIFY)
    {
        if(height < width)
            scale = height;
        else
            scale = width;
    }
    else{
        if(sscale != 0.0f)
            scale = sscale;
    }
    
    }

Window::~Window()
{
    glfwDestroyWindow(window);
}