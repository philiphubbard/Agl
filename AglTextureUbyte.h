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
//  AglTextureUbyte.h
//

#ifndef __AglTextureUbyte__
#define __AglTextureUbyte__

#include "Agl/AglTexture.h"
#include <OpenGL/gl3.h>

namespace Agl
{
    
    class TextureUbyte : public Texture
    {
    public:
        TextureUbyte(GLenum target);
        virtual ~TextureUbyte();

        // The caller retains ownership of the data.

        void    setData(GLubyte* data, GLsizei width, GLsizei height,
                        GLint internalFormat = GL_RGBA,
                        GLenum format = GL_RGBA,
                        GLint rowLength = 0, GLint skipPixels = 0,
                        GLint skipRows = 0);
        
        GLsizei width() const;
        GLsizei height() const;

    private:
        class Imp;
        std::unique_ptr<Imp> _m;
    };

}

#endif
