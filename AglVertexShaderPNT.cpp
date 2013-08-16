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

#include "AglVertexShaderPNT.h"
#include "AglShaderProgram.h"
#include "AglSurfacePNT.h"
#include <string>
#include <strstream>

namespace Agl
{
        
    class VertexShaderPNT::Imp
    {
    public:
        Imp() : positionAttribute(0), normalAttribute(0), texCoordAttribute(0) {}
        
        GLint       modelViewProjMatrixUniform;
        GLint       normalMatrixUniform;
        
        GLint       positionAttribute;
        GLint       normalAttribute;
        GLint       texCoordAttribute;
        
        Imath::M44f viewMatrix;
        Imath::M44f projMatrix;
    };
    
    VertexShaderPNT::VertexShaderPNT(const std::string& text) :
        Shader(GL_VERTEX_SHADER, text), _m(new Imp)
    {
    }
    
    VertexShaderPNT::~VertexShaderPNT()
    {
    }
    
    void VertexShaderPNT::surfaceAdded(Agl::SurfacePNT* surface)
    {
        if (id() != 0)
            postLink(surface);
    }
    
    void VertexShaderPNT::setViewMatrix(const Imath::M44f& mat)
    {
        _m->viewMatrix = mat;
    }
    
    const Imath::M44f& VertexShaderPNT::viewMatrix() const
    {
        return _m->viewMatrix;
    }
    
    void VertexShaderPNT::setProjectionMatrix(const Imath::M44f& mat)
    {
        _m->projMatrix = mat;
    }
    
    const Imath::M44f& VertexShaderPNT::projectionMatrix() const
    {
        return _m->projMatrix;
    }
    
    void VertexShaderPNT::postLink()
    {
        _m->modelViewProjMatrixUniform = glGetUniformLocation(shaderProgram()->id(),
                                                              modelViewProjectionMatrixUniformName());
        _m->normalMatrixUniform = glGetUniformLocation(shaderProgram()->id(),
                                                       normalMatrixUniformName());
        
        _m->positionAttribute = glGetAttribLocation(shaderProgram()->id(),
                                                    positionAttributeName());
        _m->normalAttribute = glGetAttribLocation(shaderProgram()->id(),
                                                  normalAttributeName());
        _m->texCoordAttribute = glGetAttribLocation(shaderProgram()->id(),
                                                    texCoordAttributeName());
        
        if (_m->modelViewProjMatrixUniform < 0)
        {
            std::strstream s;
            s << "Agl::VertexShaderPNT::postLink() \"" << typeid(*this).name() << "\":\n"
              << "modelViewProjMatrixUniform not located";
            throw std::invalid_argument(s.str());
        }

        if (_m->texCoordAttribute < 0)
        {
            std::strstream s;
            s << "Agl::VertexShaderPNT::postLink() \"" << typeid(*this).name() << "\":\n"
              << "texCoordAttribute not located";
            throw std::invalid_argument(s.str());
        }

        if (_m->positionAttribute < 0)
        {
            std::strstream s;
            s << "Agl::VertexShaderPNT::postLink() \"" << typeid(*this).name() << "\":\n"
              << "positionAttribute not located";
            throw std::invalid_argument(s.str());
        }

        if (_m->normalAttribute < 0)
        {
            std::strstream s;
            s << "Agl::VertexShaderPNT::postLink() \"" << typeid(*this).name() << "\":\n"
              << "normalAttribute not located";
            throw std::invalid_argument(s.str());
        }
    }
    
    void VertexShaderPNT::postLink(SurfacePNT* surface)
    {
        GLuint vertexArrayObject;
        glGenVertexArrays(1, &vertexArrayObject);
        glBindVertexArray(vertexArrayObject);
        
        GLuint vertexBufferObject;
        glGenBuffers(1, &vertexBufferObject);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
        
        glBufferData(GL_ARRAY_BUFFER, surface->positionsSize() + surface->normalsSize() +
                     surface->textureCoordsSize(),
                     NULL, GL_STATIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0,
                        surface->positionsSize(), surface->positions());
        glBufferSubData(GL_ARRAY_BUFFER, surface->positionsSize(),
                        surface->normalsSize(), surface->normals());
        glBufferSubData(GL_ARRAY_BUFFER, surface->positionsSize() + surface->normalsSize(),
                        surface->textureCoordsSize(), surface->textureCoords());
        
        glVertexAttribPointer((GLuint) _m->positionAttribute, 4, GL_FLOAT, GL_FALSE, 0,
                              NULL);
        glVertexAttribPointer((GLuint) _m->normalAttribute, 3, GL_FLOAT, GL_FALSE, 0,
                              (const GLvoid*) surface->positionsSize());
        glVertexAttribPointer((GLuint) _m->texCoordAttribute, 2, GL_FLOAT, GL_FALSE, 0,
                              (const GLvoid*) (surface->positionsSize() + surface->normalsSize()));
        
        glEnableVertexAttribArray((GLuint) _m->positionAttribute);
        glEnableVertexAttribArray((GLuint) _m->normalAttribute);
        glEnableVertexAttribArray((GLuint) _m->texCoordAttribute);
        
        surface->setVertexArrayObject(vertexArrayObject, shaderProgram());
    }
    
    void VertexShaderPNT::preDraw()
    {
    }
    
    void VertexShaderPNT::preDraw(SurfacePNT* surface)
    {
        // Remember that in Imath, vectors are rows, and the transformation
        // of vector V by matrix M is V * M.
        
        Imath::M44f modelView = surface->modelMatrix() * _m->viewMatrix;
        Imath::M44f modelViewProjMatrix = modelView * _m->projMatrix;
        
        // The shaders, however, follow the OpenGL tradition of considering
        // vectors to be columns, so the transformation would be M * V.
        // Since Imath::M44f::getValue() also returns the matrix in row-major
        // order and shaders expect it in column-major order, the necessary
        // transposition of the matrix occurs automatically, and the third
        // argument of glUniformMatrix4fv() does not need to be GL_TRUE
        // to specify an explicit transposition.
        
        glUniformMatrix4fv(_m->modelViewProjMatrixUniform, 1, GL_FALSE,
                           modelViewProjMatrix.getValue());
        
        Imath::M33f rot(modelView[0][0], modelView[0][1], modelView[0][2],
                        modelView[1][0], modelView[1][1], modelView[1][2],
                        modelView[2][0], modelView[2][1], modelView[2][2]);
        Imath::M33f normalMatrix = (rot.inverse()).transposed();
        
        glUniformMatrix3fv(_m->normalMatrixUniform, 1, GL_FALSE,
                           normalMatrix.getValue());
    }
    
    void VertexShaderPNT::postDraw()
    {
    }
    
}


