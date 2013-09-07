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
// AglVertexShaderPNT.h
//
// A class derived from Agl::Shader for a vertex shader compatible with
// surfaces having positions, normals and texture coordinates (the "P", "N"
// and "T").  This class serves as a base class for more specialized vertex
// shaders.
//

#ifndef __AglVertexShaderPNT__
#define __AglVertexShaderPNT__

#include "AglShader.h"
#include <OpenEXR/ImathMatrix.h>
#include <OpenGL/gl3.h>
#include <memory>

namespace Agl
{
    class SurfacePNT;
    
    class VertexShaderPNT : public Shader
    {
    public:
        
        // The code argument is the text of the GLSL shader code.
        
        VertexShaderPNT(const std::string& code);
        virtual ~VertexShaderPNT();
        
        // A derived class can redefine this virtual function to do special
        // behaviors when a surface is associated with this shader instance.
        // The derived class should then call this base class function.
        
        virtual void        surfaceAdded(SurfacePNT*);
        
        // Set and get the view matrix to be used for upcoming drawing operations
        // using this shader.
        
        void                setViewMatrix(const Imath::M44f&);
        const Imath::M44f&  viewMatrix() const;
        
        // Set and get the projection matrix to be used for upcoming drawing
        // operations using this shader.
        
        void                setProjectionMatrix(const Imath::M44f&);
        const Imath::M44f&  projectionMatrix() const;
        
        // A derived class can redefine this virtual function to do special
        // behavior after this shader is linked with its shader program.  The
        // derived class should then call this base class function.  The base
        // class function throws a std::invalid_argument exception if any of the
        // uniform or attribute variables whose names are returned by protected
        // virtual functions, below, cannot be located in the GLSL shader code.
        
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

    protected:
        
        // A derived class must redefine these virtual functions to return the
        // names used in the GLSL shader code for various uniform and attribute
        // variables.
        
        virtual const char* modelViewProjectionMatrixUniformName() const = 0;
        virtual const char* normalMatrixUniformName() const = 0;
        
        virtual const char* positionAttributeName() const = 0;
        virtual const char* normalAttributeName() const = 0;
        virtual const char* texCoordAttributeName() const = 0;
        
    private:
        
        // Details of the class' data are hidden in the .cpp file.

        class Imp;
        std::unique_ptr<Imp> _m;
    };
    
}

#endif
