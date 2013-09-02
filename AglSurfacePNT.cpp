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
// AglSurfacePNT.cpp
//

#include "AglSurfacePNT.h"
#include "AglTexture.h"
#include <map>

namespace Agl
{
        
    class SurfacePNT::Imp
    {
    public:
        std::map<GLenum, TextureUbyte*> unitToTexture;
        Imath::M44f                     modelMatrix;
    };
    
    SurfacePNT::SurfacePNT() :
        _m(new Imp)
    {
    }
    
    SurfacePNT::~SurfacePNT()
    {
    }
    
    void SurfacePNT::setTexture(TextureUbyte* texture,
                                GLenum unit)
    {
        if (unit - GL_TEXTURE0 >= Texture::maxTextureUnits())
            throw std::out_of_range("Agl::SurfacePNT::setTexture(): invalid unit");
        
        _m->unitToTexture[unit] = texture;
    }
    
    TextureUbyte* SurfacePNT::texture(GLenum unit)
    {
        if (unit - GL_TEXTURE0 >= Texture::maxTextureUnits())
            throw std::out_of_range("Agl::SurfacePNT::texture(): invalid unit");

        TextureUbyte* result = 0;
        std::map<GLenum, TextureUbyte*>::iterator it = _m->unitToTexture.find(unit);
        if (it != _m->unitToTexture.end())
            result = it->second;
        return result;
    }
    
    const TextureUbyte* SurfacePNT::texture(GLenum unit) const
    {
        if (unit - GL_TEXTURE0 >= Texture::maxTextureUnits())
            throw std::out_of_range("Agl::SurfacePNT::texture(): invalid unit");
        
        const TextureUbyte* result = 0;
        std::map<GLenum, TextureUbyte*>::iterator it = _m->unitToTexture.find(unit);
        if (it != _m->unitToTexture.end())
            result = it->second;
        return result;
    }

    void SurfacePNT::setModelMatrix(const Imath::M44f& m)
    {
        _m->modelMatrix = m;
    }
    
    const Imath::M44f& SurfacePNT::modelMatrix() const
    {
        return _m->modelMatrix;
    }
    
}


