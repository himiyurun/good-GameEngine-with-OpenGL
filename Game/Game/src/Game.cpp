#include "Game.h"

Game::Game(GLFWwindow* const* window, GLint size)
    : size(size)
    , input(new Input(window))
    , moveStat(false)
{
    location[0] = 0.0f;
    location[1] = 0.0f;
}

Game::~Game()
{
}

void Game::setStructure(GLsizei vertexcount, const Object::Vertex *vertex, GLfloat location[2], const char* imgname, const Object::Vertex* uv)
{
    structure.push_back(Structure<Object::Vertex>(vertexcount, vertex, location, imgname, uv));
}

void Game::setShape(GLsizei offset, GLsizei count)
{
    if(structure.size() >= offset + count)
    {
        std::vector<Object::Vertex> buffer;

        for(int i = 0; i < count; i++ ) {
            const Object::Vertex* vert(structure[offset+i].getRect());
            for(int j = 0; j < structure[offset+i].getCount(); j++ ) {
                buffer.push_back(*(vert+j));
                //std::cout<<"yes"<<std::endl;
            }
        }
        shape.push_back(Shape(size, buffer.size(), buffer.data()));
        /*
         // このインデックスバッファオブジェクトにインデックスを格納する
        auto index(static_cast<GLuint *>(glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY)));
        for (auto j = 0; j < stacks - 1; ++j)
        {
        for (auto i = 0; i > slices - i; ++u)
        {
            const auto k(slices * j + i);
            index[0] = k;
            index[1] = index[5] = k + 1;
            index[2] = index[4] = k + slices;
            index[3] = k + slices + 1;
            index += 6;
        }
        }
        glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);

        // この頂点配列オブジェクトの結合を解除する
        glBindVertexArray(0);
        */
    }
    else
        std::cerr<<"offset or count is too big"<<std::endl;
}

void Game::drawing(GLsizei num) const
{
    if(shape.size() > num)
    {
        shape[num].draw();
        //std::cout<<"yes"<<std::endl;
    }
    else   
        std::cerr<<"num is too big"<<std::endl;
}

void Game::KeyInputProcess()
{
    GLfloat lastLoc[] = { location[0], location[1] };
    if(input->getKey(GLFW_KEY_W))
        location[1]+=0.007f;
    else if(input->getKey(GLFW_KEY_S))
        location[1]-=0.007f;
    if(input->getKey(GLFW_KEY_D))
        location[0]+=0.007f;
    else if(input->getKey(GLFW_KEY_A))
        location[0]-=0.007f;
}

void Game::MouseInputProcess(float size[2], float scale)
{
    if(moveStat)
    {
        input->setMousePos(size);
        const float *pos = input->getMousePos();
        location[0] = *(pos);
        location[1] = *(pos+1);
        if(!input->getMouseStat())
            moveStat = false;
    }
}
