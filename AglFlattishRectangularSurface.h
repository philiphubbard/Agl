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
// AglFlattishRectuangularSurface.h
//
// A class derived from Agl::SurfacePNT to represent a tessellated rectangle
// that is either flat, or almost flat with a curved "bulge" in the Z dimension
// (the bulge being highest in the middle).  The X and Y coordinates of the
// surface's vertices run from -0.5 to 0.5.
//

#ifndef __AglFlattishRectangularSurface__
#define __AglFlattishRectangularSurface__

#include "Agl/AglSurfacePNT.h"

namespace Agl
{
    
    class FlattishRectangularSurface : public SurfacePNT
    {
    public:
        
        // The numVerticesX and numVerticesY arguments specify the resolution of
        // the tessellation.  The maxZ argument, if not 0, specifies the maximum
        // height of the "bulge" in the middle of the surface.
        
        FlattishRectangularSurface(GLsizei numVerticesX, GLsizei numVerticesY,
                                   GLfloat maxZ = 0.0f);
        virtual ~FlattishRectangularSurface();
        
        // Redefinitions of virtual functions from Agl::SurfacePNT.
        
        virtual const GLfloat* positions() const;
        virtual GLsizeiptr     positionsSize() const;
        
        virtual const GLfloat* normals() const;
        virtual GLsizeiptr     normalsSize() const;
        
        virtual const GLfloat* textureCoords() const;
        virtual GLsizeiptr     textureCoordsSize() const;
        
        // Redefinitions of virtual functions from Agl::Surface.
        
        virtual GLsizei        elementsSize() const;
        virtual GLenum         primitiveMode() const;
        
    protected:
        
        // Redefinition of a virtual function from Agl::Surface.
        // The elements are a sequence of triangle strips, where each strip runs
        // the full range of X coordinates (from -0.5 to 0.5).
        
        virtual GLuint*        elements() const;
        
    private:
        
        // Details of the class' data are hidden in the .cpp file.
        
        class Imp;
        std::unique_ptr<Imp> _m;
    };
    
}

#endif