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
//  AglShader.cpp
//

#include "AglFlattishRectangularSurface.h"

namespace Agl
{
    
    class FlattishRectangularSurface::Imp
    {
    public:
        Imp(GLfloat mz) : elements(0), elementsSize(0), vertexPositions(0),
        vertexPositionsSize(0), vertexTexCoords(0), vertexTexCoordsSize(0),
        vertexNormals(0), vertexNormalsSize(0), maxZ(mz) {}
        
        GLfloat z(GLfloat x, GLfloat y) const;
        
        GLuint*     elements;
        GLsizei     elementsSize;
        GLfloat*    vertexPositions;
        GLsizeiptr  vertexPositionsSize;
        GLfloat*    vertexTexCoords;
        GLsizeiptr  vertexTexCoordsSize;
        GLfloat*    vertexNormals;
        GLsizeiptr  vertexNormalsSize;
        GLfloat     maxZ;
    };
    
    GLfloat FlattishRectangularSurface::Imp::z(GLfloat x, GLfloat y) const
    {
        GLfloat zx = sin((x - (-0.5f)) / (0.5f - (-0.5f)) * M_PI);
        GLfloat zy = sin((y - (-0.5f)) / (0.5f - (-0.5f)) * M_PI);
        return maxZ * zx * zy;
    }
    
    FlattishRectangularSurface::FlattishRectangularSurface(GLsizei numVerticesX,
                                                           GLsizei numVerticesY,
                                                           GLfloat maxZ) :
        _m(new Imp(maxZ))
    {
        GLsizei numElements = (2 * numVerticesX + 1) * (numVerticesY - 1);
        _m->elements = new GLuint [numElements];
        _m->elementsSize = sizeof(GLuint) * numElements;
        
        GLsizei numVertices = numVerticesX * numVerticesY;
        
        _m->vertexPositions = new GLfloat [numVertices * 4];
        _m->vertexPositionsSize = sizeof(GLfloat) * numVertices * 4;
        
        _m->vertexTexCoords = new GLfloat [numVertices * 2];
        _m->vertexTexCoordsSize = sizeof(GLfloat) * numVertices * 2;
        
        _m->vertexNormals = new GLfloat [numVertices * 3];
        _m->vertexNormalsSize = sizeof(GLfloat) * numVertices * 3;
        
        GLfloat x0 = -0.5f;
        GLfloat x;
        GLfloat deltaX = 1.0f / (numVerticesX - 1);
        GLfloat y = 0.5f;
        GLfloat deltaY = -1.0f / (numVerticesY - 1);
        GLfloat z = 0.0f;
        GLfloat s0 = 0.0f;
        GLfloat s;
        GLfloat deltaS = 1.0f / (numVerticesX - 1);
        GLfloat t = 1.0f;
        GLfloat deltaT = -1.0f / (numVerticesY - 1);
        GLuint elemVertex = 0;
        GLuint elemVertexOffset = numVerticesX;
        
        size_t iPos = 0;
        size_t iTex = 0;
        size_t iNormal = 0;
        size_t iElem = 0;
        
        bool doZ = (_m->maxZ != 0.0f);
        
        for (size_t iY = 0; iY < numVerticesY; ++iY)
        {
            x = x0;
            s = s0;
            for (size_t iX = 0; iX < numVerticesX; ++iX)
            {
                if (doZ)
                    z = _m->z(x, y);
                
                _m->vertexPositions[iPos++] = x;
                _m->vertexPositions[iPos++] = y;
                _m->vertexPositions[iPos++] = z;
                _m->vertexPositions[iPos++] = 1.0f;
                x += deltaX;
                
                _m->vertexTexCoords[iTex++] = s;
                _m->vertexTexCoords[iTex++] = t;
                s += deltaS;
                
                if (doZ)
                {
                    const GLfloat dx = 1.0f / 1000.0f;
                    const GLfloat dy = dx;
                    Imath::V3f vx(dx, 0.0f, _m->z(x + dx, y) - z);
                    Imath::V3f vy(0.0f, dy, _m->z(x, y + dy) - z);
                    Imath::V3f n = (vx % vy).normalized();
                    _m->vertexNormals[iNormal++] = n[0];
                    _m->vertexNormals[iNormal++] = n[1];
                    _m->vertexNormals[iNormal++] = n[2];
                }
                else
                {
                    _m->vertexNormals[iNormal++] = 0.0f;
                    _m->vertexNormals[iNormal++] = 0.0f;
                    _m->vertexNormals[iNormal++] = 1.0f;
                }
                
                if (iY < numVerticesY - 1)
                {
                    _m->elements[iElem++] = elemVertex;
                    _m->elements[iElem++] = elemVertex++ + elemVertexOffset;
                }
            }
            y += deltaY;
            t += deltaT;
            
            if (iY < numVerticesY - 1)
                _m->elements[iElem++] = elementRestart();
        }
    }
    
    FlattishRectangularSurface::~FlattishRectangularSurface()
    {
        delete [] _m->elements;
        delete [] _m->vertexPositions;
        delete [] _m->vertexNormals;
        delete [] _m->vertexTexCoords;
    }
    
    const GLfloat* FlattishRectangularSurface::positions() const
    {
        return _m->vertexPositions;
    }
    
    GLsizeiptr FlattishRectangularSurface::positionsSize() const
    {
        return _m->vertexPositionsSize;
    }
    
    const GLfloat* FlattishRectangularSurface::normals() const
    {
        return _m->vertexNormals;
    }
    
    GLsizeiptr FlattishRectangularSurface::normalsSize() const
    {
        return _m->vertexNormalsSize;
    }
    
    const GLfloat* FlattishRectangularSurface::textureCoords() const
    {
        return _m->vertexTexCoords;
    }
    
    GLsizeiptr FlattishRectangularSurface::textureCoordsSize() const
    {
        return _m->vertexTexCoordsSize;
    }
    
    GLsizei FlattishRectangularSurface::elementsSize() const
    {
        return _m->elementsSize;
    }
    
    GLenum FlattishRectangularSurface::primitiveMode() const
    {
        return GL_TRIANGLE_STRIP;
    }

    GLuint* FlattishRectangularSurface::elements() const
    {
        return _m->elements;
    }
    
}