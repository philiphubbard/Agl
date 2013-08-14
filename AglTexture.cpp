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
//  AglTexture.cpp
//

#include "AglTexture.h"
#include <vector>
#include <map>

namespace Agl
{
        
    class Texture::Imp
    {
    public:
        Imp(GLenum t) : target(t), id(0) {}
        GLenum  target;
        GLuint  id;
        
        typedef std::map<size_t, Texture*>  TargetToTexture;
        static std::vector<TargetToTexture> unitBindings;
    };
    
    std::vector<Texture::Imp::TargetToTexture> Texture::Imp::unitBindings;
    
    Texture::Texture(GLenum target) :
        _m(new Imp(target))
    {
    }
    
    Texture::~Texture()
    {
        glDeleteTextures(1, &_m->id);
        
        // The assumption is that Texture deletion is rare, so
        // the algorithm does not need to be have special measures
        // to make it efficient.
        
        for (Imp::TargetToTexture& map : Imp::unitBindings)
        {
            Imp::TargetToTexture::iterator it = map.begin();
            while (it != map.end())
            {
                if (it->second == this)
                    map.erase(it++);
                else
                    it++;
            }
        }
    }
    
    GLenum Texture::target() const
    {
        return _m->target;
    }
    
    void Texture::build()
    {
        glGenTextures(1, &_m->id);
    }
    
    GLuint Texture::id() const
    {
        return _m->id;
    }
    
    void Texture::bind(GLenum unit)
    {
        if (unit - GL_TEXTURE0 >= maxTextureUnits())
            throw std::out_of_range("Agl::Texture::bind(): invalid unit");
        
        if (!isBound(unit))
        {
            glActiveTexture(unit);
            glBindTexture(_m->target, id());
            
            size_t u = unit - GL_TEXTURE0;
            if (Imp::unitBindings.size() <= u)
                Imp::unitBindings.resize(u + 1);
            
            Imp::unitBindings[u][_m->target] = this;
        }
    }
    
    bool Texture::isBound(GLenum unit)
    {
        if (unit - GL_TEXTURE0 >= maxTextureUnits())
            throw std::out_of_range("Agl::Texture::isBound(): invalid unit");

        bool result = false;
        
        size_t u = unit - GL_TEXTURE0;
        if (Imp::unitBindings.size() > u)
        {
            Imp::TargetToTexture& map = Imp::unitBindings[u];
            Imp::TargetToTexture::iterator it = map.find(_m->target);
            if ((it != map.end()) && (it->second == this))
                result = true;
        }
        
        return result;
    }
    
    GLsizei Texture::maxTextureUnits()
    {
        static GLsizei max = 0;
        if (max == 0)
            glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &max);
        
        return max;
    }
    
    void Texture::unbind()
    {
        GLsizei unit;
        glGetIntegerv(GL_ACTIVE_TEXTURE, &unit);

        size_t u = unit - GL_TEXTURE0;
        if (Imp::unitBindings.size() > u)
        {
            Imp::TargetToTexture& map = Imp::unitBindings[u];
            Imp::TargetToTexture::iterator it = map.find(_m->target);
            if ((it != map.end()) && (it->second != this))
                map.erase(it);
        }
    }

}


