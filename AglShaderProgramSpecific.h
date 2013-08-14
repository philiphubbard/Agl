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
//  AglShaderProgramSpecific.h
//

#ifndef __AglShaderProgramSpecific__
#define __AglShaderProgramSpecific__

#include "Agl/AglShaderProgram.h"
#include <OpenGL/gl3.h>

namespace Agl
{
    
    template <class VShader, class FShader, class Surf>
    class ShaderProgramSpecific : public ShaderProgram
    {
    public:
        ShaderProgramSpecific();
        virtual ~ShaderProgramSpecific();
        
        void            setVertexShader(VShader*);
        VShader*        vertexShader();
        const VShader*  vertexShader() const;
        
        void            setFragmentShader(FShader*);
        FShader*        fragmentShader();
        const FShader*  fragmentShader() const;
        
        void            addSurface(Surf*);
        void            removeSurface(Surf*);
        
    protected:
        virtual void    postLink();
        virtual void    preDraw();
        virtual void    drawSurfaces();
        virtual void    postDraw();
        
    private:
        class Imp;
        std::unique_ptr<Imp> _m;
    };

}

// The template definitions in the following header file should be considered
// private implementation details.

#include "Agl/AglShaderProgramSpecificImp.h"

#endif
