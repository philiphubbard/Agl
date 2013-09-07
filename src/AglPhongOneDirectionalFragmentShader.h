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
// AglPhongOneDirectionalFragmentShader.h
//
// A class derived from Agl::FragmentShaderPNT for a GLSL fragment shader
// implementing a Phong reflecton model with one directional light source.
// The implementation is based on code from "OpenGL Programming Guide (Eighth
// Edition)" by Shreiner, Sellers, Kessenich and Licea-Kane.
//

#ifndef __AglPhongOneDirectionalFragmentShader__
#define __AglPhongOneDirectionalFragmentShader__

#include "AglFragmentShaderPNT.h"
#include <OpenEXR/ImathVec.h>

namespace Agl
{
    
    class PhongOneDirectionalFragmentShader : public FragmentShaderPNT
    {
    public:
        
        PhongOneDirectionalFragmentShader();
        virtual ~PhongOneDirectionalFragmentShader();
        
        // Set and get the color of the ambient light.  Each component should
        // be between 0 and 1.
        
        void            setAmbientColor(const Imath::V3f&);
        Imath::V3f      ambientColor() const;
        
        // Set and get the color of the directional light.  Each component should
        // be between 0 and 1.
        
        void            setLightColor(const Imath::V3f&);
        Imath::V3f      lightColor() const;
        
        // Set and get the vector pointing to the light from the origin, assuming
        // the camera is at the origin looking down the negative Z axis.
        
        void            setLightDirection(const Imath::V3f&);
        Imath::V3f      lightDirection() const;
        
        // Set and get the shininess (exponent) for specular reflections.
        
        void            setShininess(GLfloat);
        GLfloat         shininess() const;
        
        // Set and get a strength factor for the specular reflection component.
        // A strength of 0 disables specular reflections.
        
        void            setStrength(GLfloat);
        GLfloat         strength() const;
        
        // Necessary because overloading one version of postLink() implicitly
        // hides the other versions from the base class.  See Scott Meyers'
        // "Effective C++: Third Edition," Item 33.
        
        using FragmentShaderPNT::postLink;
        
        // Redefinitions of virtual functions from Agl::FragmentShaderPNT.

        virtual void    postLink();
        virtual void    preDraw();
        virtual void    preDraw(SurfacePNT*);
        
    private:

        // Details of the class' data are hidden in the .cpp file.
        
        class Imp;
        std::unique_ptr<Imp> _m;
    };

}

#endif
