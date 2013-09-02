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
// AglFragmentShaderPNT.h
//
// A class derived from Agl::Shader for a fragment shader compatible with
// surfaces having positions, normals and texture coordinates (the "P", "N"
// and "T").  This class serves as a base class for more specialized fragment
// shaders.
//

#ifndef __AglFragmentShaderPNT__
#define __AglFragmentShaderPNT__

#include "Agl/AglShader.h"
#include <OpenGL/gl3.h>

namespace Agl
{
    class SurfacePNT;
    
    class FragmentShaderPNT : public Shader
    {
    public:
        
        // The code argument is the text of the GLSL shader code.
        
        FragmentShaderPNT(const std::string& code);
        virtual ~FragmentShaderPNT();
        
        // A derived class can redefine this virtual function to do special
        // behaviors when a surface is associated with this shader instance.
        // The derived class should then call this base class function.
        
        virtual void        surfaceAdded(SurfacePNT*);
        
        // A derived class can redefine this virtual function to do special
        // behavior after this shader is linked with its shader program.  The
        // derived class should then call this base class function.
        
        virtual void        postLink();
        
        // A derived class can redefine this virtual function to do special
        // surface-specific behavior after this shader is linked with its shader
        // program.  The derived class shoudl then call this base class function.
        
        virtual void        postLink(SurfacePNT*);
        
        // A derived class can redefine this virtual function to do special
        // behavior before each time this shader is used for drawing any surfaces
        // for a given frame. The derived class should then call this base class
        // function.
        
        virtual void        preDraw();

        // A derived class can redefine this virtual function to do special
        // behavior before each time this shader is used for drawing each specific
        // surface. The derived class should then call this base class function.
        
        virtual void        preDraw(SurfacePNT*);
        
        // A derived class can redefine this virtual function to do special
        // behavior after each time this shader has been used for drawing
        // all surfaces for a given frame.  The derived class should then call this
        // base class function.

        virtual void        postDraw();
    };
    
}

#endif
