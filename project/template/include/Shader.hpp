#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>

class Shader
{
    public:
        GLuint Program;
        Shader();
        Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
        void Use();
};
