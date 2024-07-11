#ifndef _GAME_H_
#define _GAME_H_

#include <memory>
#include <vector>

#include "GDK/Input.h"
#include "SEL/Structure.h"
#include "Renderer/Shape.h"

class Game
{
    const GLint size;

    std::vector<Structure<Object::Vertex>> structure;

    std::vector<Shape> shape;

protected:

    std::shared_ptr<Input> input;

    GLfloat location[2];

    GLboolean moveStat;

public:

    Game(GLFWwindow* const* window, GLint size);

    ~Game();

    void setStructure(GLsizei vertexcount, const Object::Vertex *vertex, GLfloat location[2], const char* imgname, const Object::Vertex* uv);

    void setShape(GLsizei offset, GLsizei count);

    void drawing(GLsizei num) const;

    virtual void KeyInputProcess();

    virtual void MouseInputProcess(float size[2], float scale);

    virtual void InputMode() const
    {
        input->swapInput();
    }

    void putMousePos(float position[2])
    {
        input->setMousePos(position);
    }

    void saveKeyStat(int action)
    {
        input->setKeyStat(action);
    }

    void saveMouseStat(int action)
    {
        input->setMouseStat(action);
    }
};

#endif // _GAME_H_