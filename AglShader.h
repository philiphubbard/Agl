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
//  AglShader.h
//

#ifndef __AglShader__
#define __AglShader__

// Note that when using the profile for OpenGL version 3.2, it is important
// to use the OpenGL/gl3.h header instead of the OpenGL/gl.h header (and thus
// the versions of glGenVertexArray and glBindVertexArray without the APPLE
// extension).

#include <OpenGL/gl3.h>
#include <memory>

namespace Agl
{
    
    class ShaderProgram;
    
    class Shader
    {
    public:
        Shader (GLenum type, const std::string& text);
        virtual ~Shader();
        
        GLenum               type() const;
        
        void                 build();
        GLuint               id() const;
        
        ShaderProgram*       shaderProgram();
        const ShaderProgram* shaderProgram() const;
        
    private:
        class Imp;
        std::unique_ptr<Imp> _m;
        
        // Instances cannot be copied, because copies would share OpenGL resource
        // that would get released when one instance is deleted.

        friend class ShaderProgram;
        void                 setShaderProgram(ShaderProgram*);
    };
    
}

#endif