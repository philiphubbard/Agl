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
// AglImagePool.cpp
//

#include "AglImagePool.h"
#include <thread>
#include <vector>

namespace Agl
{

    class ImagePool::Imp
    {
    public:
        Imp() : width(0), height(0), bytesPerPixel(0) {}
        GLsizei                 width;
        GLsizei                 height;
        GLsizei                 bytesPerPixel;
        std::mutex              mutex;
        std::vector<GLubyte*>   pool;
    };
    
    ImagePool::ImagePool() :
        _m(new Imp)
    {
    }
    
    ImagePool::~ImagePool()
    {
        while (!_m->pool.empty())
        {
            delete [] _m->pool.back();
            _m->pool.pop_back();
        }
    }
    
    void ImagePool::setImageSize(GLsizei width, GLsizei height,
                                 GLsizei bytesPerPixel)
    {
        std::lock_guard<std::mutex> lock(_m->mutex);
        
        if ((_m->width != 0) || (_m->height != 0) || (_m->bytesPerPixel != 0))
        {
            throw std::runtime_error("Agl::ImagePool::setImageSize() "
                                     "can be called only once");
        }
        
        _m->width = width;
        _m->height = height;
        _m->bytesPerPixel = bytesPerPixel;
    }

    GLsizei ImagePool::imageWidth() const
    {
        std::lock_guard<std::mutex> lock(_m->mutex);
        return _m->width;
    }
    
    GLsizei ImagePool::imageHeight() const
    {
        std::lock_guard<std::mutex> lock(_m->mutex);
        return _m->height;
    }
    
    GLsizei ImagePool::bytesPerPixel() const
    {
        std::lock_guard<std::mutex> lock(_m->mutex);
        return _m->bytesPerPixel;
    }
    
    GLubyte* ImagePool::alloc()
    {
        std::lock_guard<std::mutex> lock(_m->mutex);
        
        if ((_m->width == 0) || (_m->height == 0) || (_m->bytesPerPixel == 0))
        {
            throw std::runtime_error("Agl::ImagePool::setImageSize() "
                                     "must be called (once) to set a non-zero "
                                     "image size");
        }
        
        if (_m->pool.empty())
        {
            return new GLubyte [_m->width * _m->height * _m->bytesPerPixel];
        }
        else
        {
            GLubyte* result = _m->pool.back();
            _m->pool.pop_back();
            return result;
        }
    }
    
    void ImagePool::free(GLubyte* image)
    {
        std::lock_guard<std::mutex> lock(_m->mutex);
        
        _m->pool.push_back(image);
    }
}