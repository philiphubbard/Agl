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
// AglTest.cpp
//

#include "AglUtilities.h"
#include <assert.h>

namespace Agl
{
 
    void testReduceImageBy2()
    {
        std::cerr << "Starting Agl::testReduceImageBy2()\n";

        // An original image to be reduced.  The pixel values are chosen to be
        // large enough that they would cause an overflow if arithmetic on them
        // were done with GLubyte as the temporary variable type.
        
        const GLubyte orig [] = {
            100, 101,   102, 103,   104, 105,   106, 107,   108, 109,   110, 111,
            112, 113,   114, 115,   116, 117,   118, 119,   120, 121,   122, 123,
            124, 125,   126, 127,   128, 129,   130, 131,   132, 133,   134, 135,
            136, 137,   138, 139,   140, 141,   142, 143,   144, 145,   146, 147,
            149, 150,   150, 151,   152, 153,   154, 155,   156, 157,   158, 159,
            160, 161,   162, 163,   164, 165,   166, 167,   168, 169,   170, 171
        };
        
        const GLsizei width = 4;
        const GLsizei height = 4;
        const GLsizei bytesPerPixel = 2;

        // Apply the image reduction to a region within the original image.
        
        const GLsizei rowLength = 6;
        const GLsizei skipPixels = 1;
        const GLsizei skipRows = 1;
        
        GLubyte result[width / 2 * height / 2 * bytesPerPixel];
        
        reduceImageBy2(result, orig, width, height, bytesPerPixel, rowLength, skipPixels, skipRows);
        
        // Test the result by reverse engineering the arithmetic for the
        // reduction.  Since the reduction is an fairly obvious operation, this
        // reverse engineering seems reasonable.
        
        assert (result[0] == (114 + 116 + 126 + 128) / 4);
        assert (result[1] == (115 + 117 + 127 + 129) / 4);
        assert (result[2] == (118 + 120 + 130 + 132) / 4);
        assert (result[3] == (119 + 121 + 131 + 133) / 4);
        assert (result[4] == (138 + 140 + 150 + 152) / 4);
        assert (result[5] == (139 + 141 + 151 + 153) / 4);
        assert (result[6] == (142 + 144 + 154 + 156) / 4);
        assert (result[7] == (143 + 145 + 155 + 157) / 4);
        
        std::cerr << "ok\n";
    }
    
}

