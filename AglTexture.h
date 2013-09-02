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
// AglTexture.h
//
// A base class for a texture to be assigned to an Agl::Surface.
//

#ifndef __AglTexture__
#define __AglTexture__

#include <OpenGL/gl3.h>
#include <memory>

namespace Agl
{
    class Texture
    {
    public:
        
        // The target should be a valid argument for glBindTexture() (e.g.,
        // GL_TEXTURE_2D).
        
        Texture(GLenum target);
        virtual ~Texture();
        
        // Access the texture specified to the constructor.
        
        GLenum          target() const;
        
        // Generate the texture object.
        
        void            build();
        
        // Access the identifier for the texture object.
        
        GLuint          id() const;
        
        // Bind the texture to the specified texture unit.  The implementation
        // keeps track of which texture is bound, so it will not make an
        // additional call to glBindTexture() if this texture is already bound.
        // If the texture unit is not valid, a std::out_of_range exception is
        // thrown.
        
        void            bind(GLenum unit = GL_TEXTURE0);
        
        // Returns true if this texture is already bound to the specified texture
        // unit.  If the texture unit is not valid, a std::out_of_range exception
        // is thrown.
        
        bool            isBound(GLenum unit = GL_TEXTURE0);
        
        // A cache for the maximum number of texture units supported by the
        // implementation of OpenGL, to avoid unnecessary calls to
        // glGetIntegerv().
        
        static GLsizei  maxTextureUnits();
        
    protected:
        
        // Should be called by a derived class if it calls glBindTexture() to
        // set the texture data, so that isBound() does not incorrectly return
        // true for another texture.
        
        void            unbind();
        
    private:

        // Details of the class' data are hidden in the .cpp file.
        // This pattern also prevents instances from being copied, which makes
        // sense because copies would share OpenGL resource that would get
        // released when one instance is deleted.
        
        class Imp;
        std::unique_ptr<Imp> _m;
    };
 
}

#endif
