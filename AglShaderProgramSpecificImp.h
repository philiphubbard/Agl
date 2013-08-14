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
//  AglShaderProgramSpecificImp.h
//
// The template definitions in the this header file should be considered
// private implementation details.
//

#ifndef __AglShaderProgramSpecificImp_h
#define __AglShaderProgramSpecificImp_h

#include <set>

namespace Agl
{
    template <class VShader, class FShader, class Surf>
    class ShaderProgramSpecific<VShader, FShader, Surf>::Imp
    {
    public:
        Imp() : vertexShader(0), fragmentShader(0) {}
        VShader*        vertexShader;
        FShader*        fragmentShader;
        std::set<Surf*> surfaces;
    };
    
    template <class VShader, class FShader, class Surf>
    ShaderProgramSpecific<VShader, FShader, Surf>::ShaderProgramSpecific() :
    ShaderProgram(), _m(new Imp)
    {
    }
    
    template <class VShader, class FShader, class Surf>
    ShaderProgramSpecific<VShader, FShader, Surf>::~ShaderProgramSpecific()
    {
    }
    
    template <class VShader, class FShader, class Surf>
    void ShaderProgramSpecific<VShader, FShader, Surf>::setVertexShader(VShader* shader)
    {
        _m->vertexShader = shader;
        ShaderProgram::setVertexShader(shader);
    }
    
    template <class VShader, class FShader, class Surf>
    VShader* ShaderProgramSpecific<VShader, FShader, Surf>::vertexShader()
    {
        return _m->vertexShader;
    }
    
    template <class VShader, class FShader, class Surf>
    const VShader* ShaderProgramSpecific<VShader, FShader, Surf>::vertexShader() const
    {
        return _m->vertexShader;
    }
    
    template <class VShader, class FShader, class Surf>
    void ShaderProgramSpecific<VShader, FShader, Surf>::setFragmentShader(FShader* shader)
    {
        _m->fragmentShader = shader;
        ShaderProgram::setFragmentShader(shader);
    }
    
    template <class VShader, class FShader, class Surf>
    FShader* ShaderProgramSpecific<VShader, FShader, Surf>::fragmentShader()
    {
        return _m->fragmentShader;
    }
    
    template <class VShader, class FShader, class Surf>
    const FShader* ShaderProgramSpecific<VShader, FShader, Surf>::fragmentShader() const
    {
        return _m->fragmentShader;
    }
    
    template <class VShader, class FShader, class Surf>
    void ShaderProgramSpecific<VShader, FShader, Surf>::addSurface(Surf* surface)
    {
        _m->surfaces.insert(surface);
        _m->vertexShader->surfaceAdded(surface);
        _m->fragmentShader->surfaceAdded(surface);
    }
    
    template <class VShader, class FShader, class Surf>
    void ShaderProgramSpecific<VShader, FShader, Surf>::removeSurface(Surf* surface)
    {
        _m->surfaces.erase(surface);
    }
    
    template <class VShader, class FShader, class Surf>
    void ShaderProgramSpecific<VShader, FShader, Surf>::postLink()
    {
        _m->vertexShader->postLink();
        _m->fragmentShader->postLink();
        for (Surf* surface : _m->surfaces)
        {
            _m->vertexShader->postLink(surface);
            _m->fragmentShader->postLink(surface);
        }
    }
    
    template <class VShader, class FShader, class Surf>
    void ShaderProgramSpecific<VShader, FShader, Surf>::preDraw()
    {
        _m->vertexShader->preDraw();
        _m->fragmentShader->preDraw();
    }
    
    template <class VShader, class FShader, class Surf>
    void ShaderProgramSpecific<VShader, FShader, Surf>::drawSurfaces()
    {
        for (Surf* surface : _m->surfaces)
        {
            _m->vertexShader->preDraw(surface);
            _m->fragmentShader->preDraw(surface);
            surface->drawElementBuffer(this);
        }
    }

    template <class VShader, class FShader, class Surf>
    void ShaderProgramSpecific<VShader, FShader, Surf>::postDraw()
    {
        _m->vertexShader->postDraw();
        _m->fragmentShader->postDraw();
    }
    
}

#endif
