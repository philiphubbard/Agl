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
// AglSurface.h
//
// A base class for a surface to be rendered with Agl::Shader and
// Agl::ShaderProgram.
//

#ifndef __AglSurface__
#define __AglSurface__

// Note that when using the profile for OpenGL version 3.2, it is important
// to use the OpenGL/gl3.h header instead of the OpenGL/gl.h header (and thus
// the versions of glGenVertexArray and glBindVertexArray without the APPLE
// extension).

#include <OpenGL/gl3.h>
#include <memory>

namespace Agl
{
    class ShaderProgram;
    
    class Surface
    {
    public:
        
        Surface();
        virtual ~Surface();
        
        // Set and get the vertex array object for this surface and a particular
        // shader program.  If the object is not valid, then a
        // std::invalid_argument exception is thrown.
        
        void            setVertexArrayObject(GLuint vao, ShaderProgram*);
        GLuint          vertexArrayObject(ShaderProgram*) const;
        
        // Build and access the element array buffer object for this surface.  It
        // is built using the values from elements() and elementsSize().
        
        void            buildElementArrayBufferObject();
        GLuint          elementArrayBufferObject() const;
        
        // The size (in bytes) of the data returned by elements().  Must be
        // redefined by a derived class.
        
        virtual GLsizei elementsSize() const = 0;
        
        // The primitive mode (e.g., GL_TRIANGLE_STRIP) to be used when drawing
        // theelement array buffer. Must be redefined by a derived class.
        
        virtual GLenum  primitiveMode() const = 0;
        
        // Draw the element array buffer for this surface using the vertex array
        // object associated with the specified shader program.
        
        void            drawElementArrayBuffer(ShaderProgram*);
        
    protected:
        
        // The elements to go in the element buffer.  Must be redefined by a
        // derived class.
        
        virtual GLuint* elements() const = 0;
        
        // This value has been passed to glPrimitiveRestartIndex(), and can be
        // used in element indices to end one primitive and start another.
        
        static GLuint   elementRestart();
        
    private:
        
        // Details of the class' data are hidden in the .cpp file.
        // This pattern also prevents instances from being copied, which make
        // sense because copies would share OpenGL resource that would get
        // released when one instance is deleted.
        
        class Imp;
        std::unique_ptr<Imp> _m;
    };

}

#endif
