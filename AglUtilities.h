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
//  AglUtilities.h
//

#ifndef __AglUtilities__
#define __AglUtilities__

#include <OpenGL/gl3.h>
#include <iostream>

namespace Agl
{
    // On OS X, glu.h, where gluErrorString() is defined, includes GL.h.
    // To avoid potential conflicts with the gl3.h that is needed for the
    // latest OpenGL functionality, here is an alternative routine for mapping
    // glGetError() results to strings.
    
    std::string errorString(GLenum error);
    
    //
    
    void        reduceImageBy2(GLubyte* result, const GLubyte* orig,
                               GLsizei width, GLsizei height,
                               GLsizei bytesPerPixel,
                               GLsizei rowLength = 0, GLsizei skipPixels = 0,
                               GLsizei skipRows = 0);

}

#endif
