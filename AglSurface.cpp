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
//  AglSurface.cpp
//

#include "AglSurface.h"
#include "AglShaderProgram.h"
#include <map>

namespace Agl
{
    
    class Surface::Imp
    {
    public:
        Imp() : elementBufferObject(0) {}
        std::map<GLuint, GLuint>    programToVertexArrayObject;
        GLuint                      elementBufferObject;
    };
    
    Surface::Surface() :
        _m(new Imp)
    {
    }
    
    Surface::~Surface()
    {
        for (std::pair<GLuint, GLuint> elem : _m->programToVertexArrayObject)
        {
            glDeleteVertexArrays(1, &elem.second);
        }
        glDeleteBuffers(1, &_m->elementBufferObject);
    }
        
    void Surface::setVertexArrayObject(GLuint id, ShaderProgram* shaderProgram)
    {
        if (!glIsVertexArray(id))
            throw std::invalid_argument("Agl::Surface::setVertexArrayObject(): "
                                        "invalid vertex array object name");
        
        _m->programToVertexArrayObject[shaderProgram->id()] = id;
    }
    
    GLuint Surface::vertexArrayObject(ShaderProgram* shaderProgram) const
    {
        std::map<GLuint, GLuint>::iterator it =
            _m->programToVertexArrayObject.find(shaderProgram->id());
        if (it != _m->programToVertexArrayObject.end())
            return it->second;
        else
            return 0;
    }
    
    void Surface::buildElementBufferObject()
    {
        glPrimitiveRestartIndex(elementRestart());
        glEnable(GL_PRIMITIVE_RESTART);

        glGenBuffers(1, &_m->elementBufferObject);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _m->elementBufferObject);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementsSize(), elements(),
                     GL_STATIC_DRAW);
    }
    
    GLuint Surface::elementBufferObject() const
    {
        return _m->elementBufferObject;
    }
    
    void Surface::drawElementBuffer(ShaderProgram* shaderProgram)
    {
        glBindVertexArray(vertexArrayObject(shaderProgram));
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject());
        glDrawElements(primitiveMode(), elementsSize(), GL_UNSIGNED_INT, NULL);
    }
    
    GLuint Surface::elementRestart() const
    {
        return INT32_MAX;
    }

}


