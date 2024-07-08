#include <cstdlib>
#include "src/GDK/Window.h"
#include "src/GDK/Shader.h"
#include "src/Renderer/Shape.h"

constexpr Object::Vertex rectangleVertex[] = {
    {  0.5f,  0.5f },
    { -0.5f,  0.5f },
    { -0.5f, -0.5f },
    {  0.5f, -0.5f }
};

int main() {
    
    if(!glfwInit()) {
        std::cerr<<"Can't Initlize GLFW"<<std::endl;
        return 1;
    }
    atexit(glfwTerminate);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    Window window(640, 480, "Game", SPECIFY, 100.0f);

    std::unique_ptr<const Shader> program(new Shader("src/shader/shader.vert", "src/shader/shader.frag"));

    std::unique_ptr<const Shape> shape(new Shape(2, 4, rectangleVertex));

    const GLint sizeLoc(program->getUnfLoc("size"));
    const GLint locationLoc(program->getUnfLoc("location"));
    const GLint scaleLoc(program->getUnfLoc("scale"));

    while(window)
    {
        window.clearColor();

        //  ここで描画を行う
        program->use();

        glUniform1f(scaleLoc, window.getScale());
        glUniform2fv(locationLoc, 1, window.getLocation());
        glUniform2fv(sizeLoc, 1, window.getSize());

        shape->draw();

        window.swapBuffers();
    }
}