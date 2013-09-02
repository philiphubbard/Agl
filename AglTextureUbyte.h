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
// AglTextureUbyte.h
//
// A class derived from Agl::Texture for an OpenGL texture whose color components
// are unsigned bytes.
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
        
        // The target should be a valid argument for glBindTexture() (e.g.,
        // GL_TEXTURE_2D).
        
        TextureUbyte(GLenum target);
        virtual ~TextureUbyte();

        // Set the data of the texture.  Note that the mipmapping is disabled
        // for the texture, so only one piece of data is necessary.  Note also
        // that the caller retains ownership of the data.  The internalFormat and
        // format arguments have the same meanings as for glTexImage2D().  The
        // rowLength, skipPixels and skipRows arguments set the
        // GL_UNPACK_ROW_LENGTH, GL_UNPACK_SKIP_PIXELS and GL_UNPACK_SKIP_ROWS
        // parameters, respectively, allowing the texture to be set from a smaller
        // region within the data argument (if the arguments have values other
        // than their default values of 0).
        
        void    setData(GLubyte* data, GLsizei width, GLsizei height,
                        GLint internalFormat = GL_RGBA,
                        GLenum format = GL_RGBA,
                        GLint rowLength = 0, GLint skipPixels = 0,
                        GLint skipRows = 0);
        
        // Access the dimensions of the texture.
        
        GLsizei width() const;
        GLsizei height() const;

    private:

        // Details of the class' data are hidden in the .cpp file.
        
        class Imp;
        std::unique_ptr<Imp> _m;
    };

}

#endif
