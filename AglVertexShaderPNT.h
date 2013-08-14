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
//  AglVertexShaderPNT.h
//

#ifndef __AglVertexShaderPNT__
#define __AglVertexShaderPNT__

#include "Agl/AglShader.h"
#include <OpenEXR/ImathMatrix.h>
#include <OpenGL/gl3.h>
#include <memory>

namespace Agl
{
    class SurfacePNT;
    
    class VertexShaderPNT : public Shader
    {
    public:
        VertexShaderPNT(const std::string& text);
        virtual ~VertexShaderPNT();
        
        virtual void        surfaceAdded(SurfacePNT*);
        
        void                setViewMatrix(const Imath::M44f&);
        const Imath::M44f&  viewMatrix() const;
        
        void                setProjectionMatrix(const Imath::M44f&);
        const Imath::M44f&  projectionMatrix() const;
        
        // If a derived class defines this virtual function, then it needs
        // to call VertexShaderPNT::postLink(), too.
        
        virtual void        postLink();
        virtual void        postLink(SurfacePNT*);
        
        virtual void        preDraw();
        virtual void        preDraw(SurfacePNT*);

        virtual void        postDraw();

    protected:
        virtual const char* modelViewProjectionMatrixUniformName() const = 0;
        virtual const char* normalMatrixUniformName() const = 0;
        
        virtual const char* positionAttributeName() const = 0;
        virtual const char* normalAttributeName() const = 0;
        virtual const char* texCoordAttributeName() const = 0;
        
    private:
        class Imp;
        std::unique_ptr<Imp> _m;
    };
    
}

#endif
