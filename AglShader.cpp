// Copyright (c) 2013 Philip M. Hubbard
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// http://opensource.org/licenses/MIT

//
//  AglShader.cpp
//

#include "AglShader.h"
#include "AglShaderProgram.h"
#include <string>
#include <strstream>

namespace Agl
{
    
    class Shader::Imp
    {
    public:
        Imp(GLenum typ, const std::string& txt) :
            id(0), type(typ), text(txt),
            program(0) {}
        GLuint              id;
        GLenum              type;
        std::string         text;
        ShaderProgram*      program;
    };
    
    Shader::Shader(GLenum shaderType, const std::string& text) :
    _m(new Imp(shaderType, text))
    {
    }
    
    Shader::~Shader()
    {
        glDeleteShader(_m->id);
    }
    
    GLenum Shader::type() const
    {
        return _m->type;
    }
    
    void Shader::build()
    {
        _m->id = glCreateShader(_m->type);
        const GLchar* str = _m->text.c_str();
        glShaderSource(_m->id, 1, &str, 0);
        
        glCompileShader(_m->id);
        GLint compileStatus;
        glGetShaderiv(_m->id, GL_COMPILE_STATUS, &compileStatus);
        if (!compileStatus)
        {
            const GLsizei MaxErrorSize = 1024;
            char errorBuffer[MaxErrorSize];
            GLsizei errorSize;
            glGetShaderInfoLog(_m->id, MaxErrorSize, &errorSize, errorBuffer);
            
            std::strstream s;
            s << "Agl::Shader::build() \"" << typeid(*this).name() << "\":\n"
              << "glCompileShader() failed:\n" << errorBuffer;
            throw std::invalid_argument(s.str());
        }
    }
    
    GLuint Shader::id() const
    {
        return _m->id;
    }
    
    ShaderProgram* Shader::shaderProgram()
    {
        return _m->program;
    }
    
    const ShaderProgram* Shader::shaderProgram() const
    {
        return _m->program;
    }
    
   void Shader::setShaderProgram(ShaderProgram* program)
    {
        _m->program = program;
    }

}


