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
// AglBasicVertexShader.h
//
// A class derived from Agl::VertexShaderPNT for a simple GLSL vertex shader,
// which simply transforms the positions and normals and passes through the
// texture coordinates.
//

#ifndef __AglBasicVertexShader__
#define __AglBasicVertexShader__

#include "Agl/AglVertexShaderPNT.h"

namespace Agl
{
    
    class BasicVertexShader : public VertexShaderPNT
    {
    public:
        
        BasicVertexShader();
        virtual ~BasicVertexShader();
        
    protected:
        
        // Redefinitions of virtual functions from Agl::VertexShaderPNT.
        
        virtual const char* modelViewProjectionMatrixUniformName() const;
        virtual const char* normalMatrixUniformName() const;
        
        virtual const char* positionAttributeName() const;
        virtual const char* normalAttributeName() const;
        virtual const char* texCoordAttributeName() const;
        
    private:

        // Details of the class' data are hidden in the .cpp file.
        
        class Imp;
        std::unique_ptr<Imp> _m;
    };
    
}

#endif
