#ifndef _SHADER_H_
#define _SHADER_H_
#include <iostream>
#include <fstream>
#include <vector>
#include <glad/glad.h>

class Shader
{
    const GLuint program;

public:

    //  コンストラクタ・・・シェーダープログラムの作成
    //  vsrc : バーテックスシェーダソースファイル
    //  fsrc : フラグメントシェーダソースファイル
    Shader(const char* vsrc, const char* fsrc);

    //  デストラクタ
    ~Shader();

    virtual GLuint createProgram(const char* vert, const char* frag);

    virtual char* (getsrc(const char* name));

    virtual GLboolean getShaderInfoLog(GLuint shader, const char* name);

    virtual GLboolean getProgramInfoLog(GLuint shader);

    void use() const
    {
        glUseProgram(program);
    }

    GLint getUnfLoc(const char* name) const { return glGetUniformLocation(program, name); }

    GLint getAtrLoc(const char* name) const { return glGetUniformLocation(program, name); }
};

#endif // _SHADER_H_