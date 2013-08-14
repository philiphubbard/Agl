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
//  AglShaderProgram.h
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
        
        void            build();
        GLuint          id() const;
        
        // Passing DoReportErrors makes a call to glGetError() at the end of
        // the routine, which can impact performance.
        
        enum ReportErrors {DoReportErrors, DoNotReportErrors};
        void            draw(ReportErrors report = DoNotReportErrors);

    protected:
        void            setVertexShader(Shader*);
        void            setFragmentShader(Shader*);
        virtual void    postLink();
        
        virtual void    preDraw();
        virtual void    drawSurfaces() = 0;
        virtual void    postDraw();

    private:
        class Imp;
        std::unique_ptr<Imp> _m;
        
        // Instances cannot be copied, because copies would share OpenGL resource
        // that would get released when one instance is deleted.
    };
    
}

#endif
