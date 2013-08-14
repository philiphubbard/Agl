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
//  AglShaderProgram.cpp
//

#include "AglShaderProgram.h"
#include "AglShader.h"
#include "AglUtilities.h"
#include <strstream>

namespace Agl
{
       
    class ShaderProgram::Imp
    {
    public:
        Imp() : id(0), vertexShader(0), fragmentShader(0) {}
        GLuint  id;
        Shader* vertexShader;
        Shader* fragmentShader;
    };
    
    ShaderProgram::ShaderProgram() :
        _m(new Imp)
    {
    }
    
    ShaderProgram::~ShaderProgram()
    {
        glDetachShader(_m->id, _m->vertexShader->id());
        glDetachShader(_m->id, _m->fragmentShader->id());
        glDeleteProgram(_m->id);
    }
    
    void ShaderProgram::build()
    {
        if (!_m->vertexShader)
        {
            std::strstream s;
            s << "Agl::ShaderProgram::build() \"" << typeid(*this).name() << "\":\n"
              << "no vertex shader";
            throw std::invalid_argument(s.str());
        }
        
        if (!_m->fragmentShader)
        {
            std::strstream s;
            s << "Agl::ShaderProgram::build() \"" << typeid(*this).name() << "\":\n"
              << "no fragment shader";
            throw std::invalid_argument(s.str());
        }
                
        if (_m->vertexShader->id() == 0)
            _m->vertexShader->build();
        if (_m->fragmentShader->id() == 0)
            _m->fragmentShader->build();
        
        _m->id = glCreateProgram();
        
        glAttachShader(_m->id, _m->vertexShader->id());
        glAttachShader(_m->id, _m->fragmentShader->id());
        
        glLinkProgram(_m->id);
        GLint linkStatus;
        glGetProgramiv(_m->id, GL_LINK_STATUS, &linkStatus);
        if (!linkStatus)
        {
            const GLsizei MaxErrorSize = 1024;
            char errorBuffer[MaxErrorSize];
            GLsizei errorSize;
            glGetProgramInfoLog(_m->id, MaxErrorSize, &errorSize, errorBuffer);
            
            std::strstream s;
            s << "Agl::ShaderProgram::build() \"" << typeid(*this).name() << "\":\n"
              << "\" glLinkProgram() failed:\n" << errorBuffer;
            throw std::invalid_argument(s.str());
        }

        postLink();
    }
    
    GLuint ShaderProgram::id() const
    {
        return _m->id;
    }
    
    void ShaderProgram::draw(ReportErrors reportErrors)
    {
        if (!id() || !_m->vertexShader || !_m->fragmentShader)
            return;
        
        glUseProgram(_m->id);
        
        preDraw();
        drawSurfaces();
        
        if (reportErrors == DoReportErrors)
        {
            GLenum error = glGetError();
            if (error != GL_NO_ERROR)
                throw std::runtime_error(Agl::errorString(error));
        }
    }
    
    void ShaderProgram::setVertexShader(Agl::Shader* shader)
    {
        if (shader->type() != GL_VERTEX_SHADER)
        {
            std::strstream s;
            s << "Agl::ShaderProgram::setVertexShader() \""
              << typeid(*this).name() << "\":\n"
              << "not a vertex shader";
            throw std::invalid_argument(s.str());
        }
        
        _m->vertexShader = shader;
        shader->setShaderProgram(this);
    }
    
    void ShaderProgram::setFragmentShader(Agl::Shader* shader)
    {
        if (shader->type() != GL_FRAGMENT_SHADER)
        {
            std::strstream s;
            s << "Agl::ShaderProgram::setFragmentShader() \""
              << typeid(*this).name() << "\":\n"
              << "not a fragment shader";
            throw std::invalid_argument(s.str());
        }

        _m->fragmentShader = shader;
        shader->setShaderProgram(this);
    }
    
    void ShaderProgram::postLink()
    {
    }
    
    void ShaderProgram::preDraw()
    {
    }
    
    void ShaderProgram::postDraw()
    {
    }

}


