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
//  AglBasicVertexShader.cpp
//

#include "AglBasicVertexShader.h"
#include <OpenGL/gl3.h>

namespace Agl
{
    
    class BasicVertexShader::Imp
    {
    public:
        static const char*  text;
        GLint               defaultTextureWrapS;
        GLint               defaultTextureWrapT;
    };
    
    const char* BasicVertexShader::Imp::text =
    "#version 150\n"
    "uniform mat4 modelViewProjMatrix;\n"
    "uniform mat3 normalMatrix;\n"
    "in vec4 in_position;\n"
    "in vec2 in_texCoord;\n"
    "in vec3 in_normal;\n"
    "out vec2 vs_texCoord;\n"
    "out vec3 vs_normal;\n"
    "void main()\n"
    "{\n"
    "    gl_Position = modelViewProjMatrix * in_position;\n"
    "    vs_texCoord = in_texCoord;"
    "    vs_normal = normalize(normalMatrix * in_normal);\n"
    "}\n";
    
    BasicVertexShader::BasicVertexShader() :
        VertexShaderPNT(Imp::text), _m(new Imp)
    {
    }
    
    BasicVertexShader::~BasicVertexShader()
    {
    }
    
    const char* BasicVertexShader::modelViewProjectionMatrixUniformName() const
    {
        return "modelViewProjMatrix";
    }
    
    const char* BasicVertexShader::normalMatrixUniformName() const
    {
        return "normalMatrix";
    }
    
    const char* BasicVertexShader::positionAttributeName() const
    {
        return "in_position";
    }
    
    const char* BasicVertexShader::normalAttributeName() const
    {
        return "in_normal";
    }
    
    const char* BasicVertexShader::texCoordAttributeName() const
    {
        return "in_texCoord";
    }
    
}


