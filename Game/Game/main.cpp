#include <cstdlib>
#include "src/GDK/Window.h"
#include "src/GDK/Shader.h"
//#include "src/Renderer/Shape.h"
//#include "src\SEL\Structure.h"

constexpr Object::Vertex rectangleVertex[] = {
    {  0.5f,  0.5f },
    { -0.5f,  0.5f },
    { -0.5f, -0.5f },
    {  0.5f, -0.5f }
};

constexpr Object::Vertex recttest[] = {
    {  0.5f,  0.5f },
    { -0.5f,  0.5f },
    { -0.5f, -0.5f },
    {  0.5f, -0.5f }
};

GLfloat position[] = { 0.0f, 0.0f };

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
    Window window(640, 480, "Game", 2, SPECIFY, 100.0f);

    std::unique_ptr<const Shader> program(new Shader("src/shader/shader.vert", "src/shader/shader.frag"));
    std::unique_ptr<const Shader> test(new Shader("src/shader/test.vert", "src/shader/shader.frag"));

    window.setStructure(4, recttest, position, NULL, NULL);
    window.setShape(0, 1);

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

        test->use();

        glUniform1f(0, window.getScale());
        glUniform2fv(1, 1, window.getSize());

        window.drawing(0);

        window.swapBuffers();
    }
}