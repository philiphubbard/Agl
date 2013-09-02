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
// AglShaderProgram.h
//
// A base class for an OpenGL shader program.
//

#ifndef __AglShaderProgram__
#define __AglShaderProgram__

#include <OpenGL/gl3.h>
#include <memory>

namespace Agl
{

    class Shader;
    
    class ShaderProgram
    {
    public:
        
        ShaderProgram();
        virtual ~ShaderProgram();
        
        // Create the program, compile and link its shaders.  Any errors cause
        // std::invalid_argument exceptions to be thrown.
        
        void            build();
        
        // Access the identifier for the successfully built shader program.
        
        GLuint          id() const;
        
        // Draw all the surfaces associated with this shader program.
        // Passing DoReportErrors makes a call to glGetError() at the end of
        // the routine, which can impact performance.
        
        enum ReportErrors {DoReportErrors, DoNotReportErrors};
        
        void            draw(ReportErrors report = DoNotReportErrors);

    protected:
        
        // Only a derived class can set the shaders.  This approach allows a
        // derived class like the ShaderProgramSpecific template to set only
        // compatible shaders.  If the argument shader is not a vertex or fragment
        // shader, then a std::invalid_argument exception is thrown.
        
        void            setVertexShader(Shader*);
        void            setFragmentShader(Shader*);
        
        virtual void    postLink();
        
        // A derived class can redefine this virtual function for special
        // behaviors to occur just before drawing surfaces.  The derived class
        // should then call this base class function.
        
        virtual void    preDraw();
        
        // A derived class must redefine this virtual function to provide the
        // details of drawing all the surfaces associated with this shader
        // program.  This approach makes sense for given that a derived class
        // like the ShaderProgramSpecific template keeps track of the compatible
        // surfaces.
        
        virtual void    drawSurfaces() = 0;
        
        // A derived class can redefine this virtual function for special
        // behaviors to occur just after drawing surfaces.  The derived class
        // should then call this base class function.
        
        virtual void    postDraw();

    private:

        // Details of the class' data are hidden in the .cpp file.
        // This pattern also prevents instances from being copied, which make
        // sense because copies would share OpenGL resource that would get
        // released when one instance is deleted.
        
        class Imp;
        std::unique_ptr<Imp> _m;
    };
    
}

#endif
