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
//  AglSurfacePNT.h
//

#ifndef __AglSurfacePNT__
#define __AglSurfacePNT__

#include "Agl/AglSurface.h"
#include <OpenEXR/ImathMatrix.h>
#include <OpenGL/gl3.h>
#include <memory>

namespace Agl
{
    
    class TextureUbyte;
    
    // PNT stands for "Position, Normal, Texture coordinate".
    
    class SurfacePNT : public Surface
    {
    public:
        SurfacePNT();
        virtual ~SurfacePNT();

        virtual const GLfloat* positions() const = 0;
        virtual GLsizeiptr     positionsSize() const = 0;

        virtual const GLfloat* normals() const = 0;
        virtual GLsizeiptr     normalsSize() const = 0;

        virtual const GLfloat* textureCoords() const = 0;
        virtual GLsizeiptr     textureCoordsSize() const = 0;
        
        void                   setTexture(TextureUbyte*,
                                          GLenum unit = GL_TEXTURE0);
        TextureUbyte*          texture(GLenum unit = GL_TEXTURE0);
        const TextureUbyte*    texture(GLenum unit = GL_TEXTURE0) const;
        
        void                   setModelMatrix(const Imath::M44f&);
        const Imath::M44f&     modelMatrix() const;

    private:
        class Imp;
        std::unique_ptr<Imp> _m;
    };

}

#endif
