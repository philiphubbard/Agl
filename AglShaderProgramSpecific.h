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
// AglShaderProgramSpecific.h
//
// A template class derived from Agl::ShaderProgram, with the template arguments
// specifying a vertex shader class, a fragment shader class, and a surface
// class that are mutually compatiable.  The API of the template class performs
// type checking for associations between instances of the shader classes and
// of the surface class.
//

#ifndef __AglShaderProgramSpecific__
#define __AglShaderProgramSpecific__

#include "Agl/AglShaderProgram.h"
#include <OpenGL/gl3.h>

namespace Agl
{
    
    // VShader is the vertex shader class, FShader is the fragment shader
    // class, Surf is the surface class.
    
    template <class VShader, class FShader, class Surf>
    class ShaderProgramSpecific : public ShaderProgram
    {
    public:
        
        ShaderProgramSpecific();
        virtual ~ShaderProgramSpecific();
        
        // Set the vertex shader instance for this shader program.  If the
        // argument shader is not a vertex shader, then a std::invalid_argument
        // exception is thrown.
        
        void            setVertexShader(VShader*);
        
        // Access the vertex shader instance for this shader program.
        
        VShader*        vertexShader();
        const VShader*  vertexShader() const;
        
        // Set the fragment shader instance for this shader program.  If the
        // argument shader is not a fragment shader, then a std::invalid_argument
        // exception is thrown.
        
        void            setFragmentShader(FShader*);
        
        // Access the fragment shader instance for this shader program.
        
        FShader*        fragmentShader();
        const FShader*  fragmentShader() const;
        
        // Associate the specified surface with this shader program, so that
        // surface will be among those drawn by the inherited draw() function.
        
        void            addSurface(Surf*);
        
        // Remove the association between the specified surface and this shader
        // program.
        
        void            removeSurface(Surf*);
        
    protected:
        
        // Redefinitions of virtual functions from Agl::ShaderProgram.
        
        virtual void    postLink();
        virtual void    preDraw();
        virtual void    drawSurfaces();
        virtual void    postDraw();
        
    private:
        
        // Details of the class' data are "hidden" in the Imp.h file.
        // This pattern also prevents instances from being copied, which makes
        // sense because copies would share OpenGL resource that would get
        // released when one instance is deleted.

        class Imp;
        std::unique_ptr<Imp> _m;
    };

}

// The template definitions in the following header file should be considered
// private implementation details.

#include "Agl/AglShaderProgramSpecificImp.h"

#endif
