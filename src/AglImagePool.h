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
// AglImagePool.h
//
// A class to manage the memory for images, avoiding unnecessary allocations
// when one thread repeatedly produces images that are consumed by another
// thread.  Memory allocated by the producer and freed by the consumer is
// retained in a pool, so actual allocations are necessary only if the producer
// gets ahead of the consumer.  Since the class is designed to support the
// producer and consumer being in separate threads, the operations of this class
// are thread safe.
//

#ifndef __AglImagePool__
#define __AglImagePool__

#include <OpenGL/gl3.h>
#include <memory>

namespace Agl
{
    class ImagePool
    {
    public:
        
        ImagePool();
        ~ImagePool();
        
        // Set the size of images that will be managed by this class.  If this
        // routine is called to set the image size to be non-zero more than once,
        // a std::runtime_error exception is thrown.
        
        void        setImageSize (GLsizei width, GLsizei height,
                                  GLsizei bytesPerPixel);
        
        // Access the size of the images managed by this class.
        
        GLsizei     imageWidth() const;
        GLsizei     imageHeight() const;
        GLsizei     bytesPerPixel() const;
        
        // Obtain image memory from the pool.  If setImageSize() has not been
        // called to set the image size to be non-zero, a std::runtime_error
        // exception is thrown.
        
        GLubyte*    alloc();
        
        // Return image memory to the pool for reuse.
        
        void        free(GLubyte*);
        
    private:

        // Details of the class' data are hidden in the .cpp file.
        
        class Imp;
        std::unique_ptr<Imp> _m;
    };
}

#endif
