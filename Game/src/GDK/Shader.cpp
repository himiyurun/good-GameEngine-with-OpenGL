#include "Shader.h"


Shader::Shader(const char* vsrc, const char* fsrc)
    : program(createProgram(vsrc, fsrc))
    {

    }

Shader::~Shader()
{
    if(program!=0)
    {
        glDeleteProgram(program);
    }
}

GLuint Shader::createProgram(const char *vert, const char *frag)
{
    const GLuint shader(glCreateProgram());
    if(vert != nullptr)
    {
        const GLuint vobj(glCreateShader(GL_VERTEX_SHADER));
        const char *src(getsrc(vert));
        if(src != nullptr)
        {
            glShaderSource(vobj, 1, &src, NULL);
            glCompileShader(vobj);
            if(getShaderInfoLog(vobj, "Vertex Shader"))
                glAttachShader(shader, vobj);
        }
        glDeleteShader(vobj);
    }

    if(frag != nullptr)
    {
        const GLuint fobj(glCreateShader(GL_FRAGMENT_SHADER));
        const char *src(getsrc(frag));
        if(src != nullptr)
        {
            glShaderSource(fobj, 1, &src, NULL);
            glCompileShader(fobj);
            if(getShaderInfoLog(fobj, "Fragment Shader"))
                glAttachShader(shader, fobj);
        }
        glDeleteShader(fobj);
    }

    glBindAttribLocation(shader, 0, "position");
    glBindFragDataLocation(shader, 0, "fragment");
    glLinkProgram(shader);

    if(getProgramInfoLog(shader))
        return shader;
    
    glDeleteProgram(shader);
    return 0;
}

GLboolean Shader::getShaderInfoLog(GLuint shader, const char *name)
{
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if(!status)
        std::cerr<<name<<" compile is Failed!!"<<std::endl;

    GLsizei bufSiz;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &bufSiz);

    if(bufSiz > 1)
    {
        std::vector<GLchar> Log(bufSiz);
        GLsizei length;
        glGetShaderInfoLog(shader,bufSiz,&length,Log.data());
        std::cerr<<&Log[0]<<std::endl;
    }

    return static_cast<GLboolean>(status);
}

GLboolean Shader::getProgramInfoLog(GLuint shader)
{
    GLint status;
    glGetProgramiv(shader, GL_LINK_STATUS, &status);
    if(!status)
        std::cerr<<"Program compile Failed!!"<<std::endl;

    GLsizei bufSiz;
    glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &bufSiz);

    if(bufSiz > 1)
    {
        std::vector<GLchar> Log(bufSiz);
        GLsizei length;
        glGetProgramInfoLog(shader, bufSiz, &length, Log.data());
        std::cerr<<&Log[0]<<std::endl;
    }

    return static_cast<GLboolean>(status);
}

char* (Shader::getsrc(const char* name))
{
    std::vector<char> buf;
    std::ifstream file;

    file.open(name, std::ios::binary);
    if(file.fail())
    {
        std::cerr<<"Can't open "<<name<<std::endl;
        file.close();
        return nullptr;
    }

    file.seekg(0L, std::ios::end);
    size_t bufSize(static_cast<size_t>(file.tellg()));
    file.seekg(0L, std::ios::beg);
    buf.resize(bufSize);
    file.read(buf.data(), bufSize);
    buf[bufSize] = '\0';
    if(file.fail())
    {
        std::cerr<<"Can't read "<<name<<std::endl;
        file.close();
        return nullptr;
    }

    file.close();

    char* src(buf.data());
    return src;
}