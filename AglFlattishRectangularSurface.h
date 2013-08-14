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
//  AglFlattishRectuangularSurface.h
//

#ifndef __AglFlattishRectangularSurface__
#define __AglFlattishRectangularSurface__

#include "Agl/AglSurfacePNT.h"

namespace Agl
{
    
    class FlattishRectangularSurface : public SurfacePNT
    {
    public:
        FlattishRectangularSurface(GLsizei numVerticesX, GLsizei numVerticesY,
                                   GLfloat maxZ = 0.0f);
        virtual ~FlattishRectangularSurface();
        
        virtual const GLfloat* positions() const;
        virtual GLsizeiptr     positionsSize() const;
        
        virtual const GLfloat* normals() const;
        virtual GLsizeiptr     normalsSize() const;
        
        virtual const GLfloat* textureCoords() const;
        virtual GLsizeiptr     textureCoordsSize() const;
        
        virtual GLsizei        elementsSize() const;
        virtual GLenum         primitiveMode() const;
        
    protected:
        virtual GLuint*        elements() const;
        
    private:
        class Imp;
        std::unique_ptr<Imp> _m;
    };
    
}

#endif