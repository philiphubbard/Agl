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
// AglShader.h
//
// A base class for a GLSL shader.
//

#ifndef __AglShader__
#define __AglShader__

#include <OpenGL/gl3.h>
#include <memory>

namespace Agl
{
    
    class ShaderProgram;
    
    class Shader
    {
    public:
        
        // The type argument is the OpenGL shader type, like GL_VERTEX_SHADER or
        // GL_FRAGMENT_SHADER.  The code argument is the text of the GLSL shader
        // code.
        
        Shader (GLenum type, const std::string& code);
        virtual ~Shader();
        
        // Access the OpenGL shader type.
        
        GLenum               type() const;
        
        // Compile the shader.  Any errors cause std::invalid_argument exceptions
        // to be thrown.
        
        void                 build();
        
        // Access the identifier for the successfully built shader.
        
        GLuint               id() const;
        
        // Access the ShaderProgram with which this shader is associated.
        
        ShaderProgram*       shaderProgram();
        const ShaderProgram* shaderProgram() const;
        
    private:
        
        // Details of the class' data are hidden in the .cpp file.
        // This pattern also prevents instances from being copied, which makes
        // sense  because copies would share OpenGL resource that would get
        // released when one instance is deleted.

        class Imp;
        std::unique_ptr<Imp> _m;
        
        // The ShaderProgram associates itself with this shader.

        friend class ShaderProgram;
        void                 setShaderProgram(ShaderProgram*);
    };
    
}

#endif