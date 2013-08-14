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
//  AglUtilities.cpp
//

#include "AglUtilities.h"

namespace Agl
{
        std::string errorString(GLenum error)
    {
        switch (error)
        {
            case GL_NO_ERROR:
                return "";
            case GL_INVALID_ENUM:
                return "GL_INVALID_ENUM";
            case GL_INVALID_VALUE:
                return "GL_INVALID_VALUE";
            case GL_INVALID_OPERATION:
                return "GL_INVALID_OPERATION";
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                return "GL_INVALID_FRAMEBUFFER_OPERATION";
            case GL_OUT_OF_MEMORY:
                return "GL_OUT_OF_MEMORY";
            default:
                return "unknown OpenGL error";
        }
    }
    
    void reduceImageBy2(GLubyte* result, const GLubyte* orig,
                        GLsizei width, GLsizei height, GLsizei bytesPerPixel,
                        GLsizei rowLength, GLsizei skipPixels, GLsizei skipRows)
    {
        if (rowLength == 0)
            rowLength = width;
        
        const GLubyte* origPtr0a = orig + bytesPerPixel * (skipRows * rowLength + skipPixels);
        const GLubyte* origPtr0b = origPtr0a + bytesPerPixel;
        const GLubyte* origPtr1a = origPtr0a + rowLength * bytesPerPixel;
        const GLubyte* origPtr1b = origPtr1a + bytesPerPixel;
        GLubyte *resultPtr = result;
        
        GLsizei resultWidth = width / 2;
        GLsizei resultHeight = height / 2;
        
        GLsizei toNextRowOrig = (2 * rowLength - width) * bytesPerPixel;
        
        for (size_t i = 0; i < resultHeight; ++i)
        {
            for (size_t j = 0; j < resultWidth; ++j)
            {
                for (size_t k = 0; k < bytesPerPixel; ++k)
                {
                    GLuint r = *origPtr0a++ + *origPtr0b++ + *origPtr1a++ + *origPtr1b++;
                    *resultPtr++ = r / 4;
                }
                origPtr0a += bytesPerPixel;
                origPtr0b += bytesPerPixel;
                origPtr1a += bytesPerPixel;
                origPtr1b += bytesPerPixel;
            }
            origPtr0a += toNextRowOrig;
            origPtr0b += toNextRowOrig;
            origPtr1a += toNextRowOrig;
            origPtr1b += toNextRowOrig;
        }
    }

}