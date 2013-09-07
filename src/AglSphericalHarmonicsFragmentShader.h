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
// AglSphericalHarmonicsFragmentShader.h
//
// A class derived from Agl::FragmentShaderPNT for a GLSL fragment shader
// implementing the Ramamoorthi and Hanrahan algorithm for diffuse shading
// using spherical harmonics.  The implementation is based on code from
// "OpenGL Programming Guide (Eighth Edition)" by Shreiner, Sellers, Kessenich and
// Licea-Kane, using light-probe image data for Old Town Square, Fort Collins, CO.
//

#ifndef __AglSphericalHarmonicsFragmentShader__
#define __AglSphericalHarmonicsFragmentShader__

#include "AglFragmentShaderPNT.h"

namespace Agl
{
    
    class SphericalHarmonicsFragmentShader : public FragmentShaderPNT
    {
    public:
        
        SphericalHarmonicsFragmentShader();
        virtual ~SphericalHarmonicsFragmentShader();
        
        // Necessary because overloading one version of preDraw() implicitly
        // hides the other versions from the base class.  See Scott Meyers'
        // "Effective C++: Third Edition," Item 33.
        
        using FragmentShaderPNT::preDraw;
        
        // Redefinition of a virtual function from Agl::FragmentShaderPNT.
        
        virtual void    preDraw(SurfacePNT*);
        
    private:
        
        // Details of the class' data are hidden in the .cpp file.
        
        class Imp;
        std::unique_ptr<Imp> _m;
    };
    
}

#endif