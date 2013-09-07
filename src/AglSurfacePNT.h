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
// AglSurfacePNT.h
//
// A class derived from Agl::Surface for a surface having positions, normals and
// texture coordinates (the "P", "N" and "T").  This class serves as a base class
// for more specialized surfaces.
//

#ifndef __AglSurfacePNT__
#define __AglSurfacePNT__

#include "AglSurface.h"
#include <OpenEXR/ImathMatrix.h>
#include <OpenGL/gl3.h>
#include <memory>

namespace Agl
{
    
    class TextureUbyte;
    
    class SurfacePNT : public Surface
    {
    public:
        
        SurfacePNT();
        virtual ~SurfacePNT();

        // A derived class must redefine this virtual function to return the
        // array of positions for the vertices of the surface (each position
        // being four coordinates, X, Y, Z, W).
        
        virtual const GLfloat* positions() const = 0;
        
        // A derived class must redefine this virtual function to return the
        // size (in bytes) of the value returned by positions().
        
        virtual GLsizeiptr     positionsSize() const = 0;

        // A derived class must redefine this virtual function to return the
        // array of normal vectors for the vertices of the surface (each normal
        // being three coordinates, X, Y, Z).
        
        virtual const GLfloat* normals() const = 0;

        // A derived class must redefine this virtual function to return the
        // size (in bytes) of the value returned by normals().
        
        virtual GLsizeiptr     normalsSize() const = 0;

        // A derived class must redefine this virtual function to return the
        // array of texture coordinates for the vertices of the surface (each
        // element of the texture coordinates being two values, S and T).
        
        virtual const GLfloat* textureCoords() const = 0;

        // A derived class must redefine this virtual function to return the
        // size (in bytes) of the value returned by textureCoords().
        
        virtual GLsizeiptr     textureCoordsSize() const = 0;
        
        // Set this surface to use the specified texture for the specified
        // texture unit.  If the texture unit is invalid, a std::out_of_range
        // exception is thrown.
        
        void                   setTexture(TextureUbyte*,
                                          GLenum unit = GL_TEXTURE0);
        
        // Access the texture being used by this surface for the specified
        // texture unit.  If the texture unit is invalid, a std::out_of_range
        // exception is thrown.
        
        TextureUbyte*          texture(GLenum unit = GL_TEXTURE0);
        const TextureUbyte*    texture(GLenum unit = GL_TEXTURE0) const;
        
        // Set and get the model matrix to be used to transform this surface
        // before drawing it.
        
        void                   setModelMatrix(const Imath::M44f&);
        const Imath::M44f&     modelMatrix() const;

    private:
        
        // Details of the class' data are hidden in the .cpp file.
        
        class Imp;
        std::unique_ptr<Imp> _m;
    };

}

#endif
