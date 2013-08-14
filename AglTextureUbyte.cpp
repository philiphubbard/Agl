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
//  AglTextureUbyte.cpp
//

#include "AglTextureUbyte.h"

namespace Agl
{
    
    class TextureUbyte::Imp
    {
    public:
        Imp() : width(0), height(0) {}
        GLsizei     width;
        GLsizei     height;
    };
    
    TextureUbyte::TextureUbyte(GLenum target) :
        Texture(target), _m(new Imp)
    {
    }
    
    TextureUbyte::~TextureUbyte()
    {
    }
    
    void TextureUbyte::setData(GLubyte* data, GLsizei width, GLsizei height,
                               GLint internalFormat, GLenum format,
                               GLint rowLength, GLint skipPixels, GLint skipRows)
    {
        _m->width = width;
        _m->height = height;
    
        glBindTexture(target(), id());
        
        glPixelStorei(GL_UNPACK_ROW_LENGTH, rowLength);
        glPixelStorei(GL_UNPACK_SKIP_PIXELS, skipPixels);
        glPixelStorei(GL_UNPACK_SKIP_ROWS, skipRows);
        
        // TODO: Replace with glTexStorage2D() and glTexSubImage2D(), when
        // the former becomes available on OS X.
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
        
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0,
                     format, GL_UNSIGNED_BYTE, data);
        
        // Make certain Texture::isBound() does not incorrectly return true for
        // another texture.

        unbind();
    }
    
    GLsizei TextureUbyte::width() const
    {
        return _m->width;
    }
    
    GLsizei TextureUbyte::height() const
    {
        return _m->height;
    }

}


