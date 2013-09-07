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
// AglSphericalHarmonicsFragmentShader.cpp
//

#include "AglSphericalHarmonicsFragmentShader.h"
#include "AglSurfacePNT.h"
#include "AglTextureUbyte.h"

namespace Agl
{
    
    class SphericalHarmonicsFragmentShader::Imp
    {
    public:
        static const char* code;
    };
    
    const char* SphericalHarmonicsFragmentShader::Imp::code =
    "#version 150\n"
    "uniform sampler2D tex;\n"
    "in vec2 vs_texCoord;\n"
    "in vec3 vs_normal;\n"
    "out vec4 fs_color;\n"
    "const float C1 = 0.429043;\n"
    "const float C2 = 0.511664;\n"
    "const float C3 = 0.743125;\n"
    "const float C4 = 0.886227;\n"
    "const float C5 = 0.247708;\n"
    "const vec3 L00 =  vec3( 0.871297,  0.875222,  0.864470);\n"
    "const vec3 L1m1 = vec3( 0.175058,  0.245335,  0.312891);\n"
    "const vec3 L10  = vec3( 0.034675,  0.036107,  0.037362);\n"
    "const vec3 L11  = vec3(-0.004629, -0.029448, -0.048028);\n"
    "const vec3 L2m2 = vec3(-0.120535, -0.121160, -0.117507);\n"
    "const vec3 L2m1 = vec3( 0.003242,  0.003624,  0.007511);\n"
    "const vec3 L20  = vec3(-0.028667, -0.024926, -0.020998);\n"
    "const vec3 L21  = vec3(-0.077539, -0.086325, -0.091591);\n"
    "const vec3 L22  = vec3(-0.161784, -0.191783, -0.219152);\n"
    "void main()\n"
    "{\n"
    "    vec3 scattered = C1 * L22 * (vs_normal.x * vs_normal.x -\n"
    "                                 vs_normal.y * vs_normal.y) +\n"
    "                     C3 * L20 * vs_normal.z * vs_normal.z +\n"
    "                     C4 * L00 -\n"
    "                     C5 * L20 +\n"
    "                     2.0 * C1 * L2m2 * vs_normal.x * vs_normal.y +\n"
    "                     2.0 * C1 * L21 * vs_normal.x * vs_normal.z +\n"
    "                     2.0 * C1 * L2m1 * vs_normal.y * vs_normal.z +\n"
    "                     2.0 * C2 * L11 * vs_normal.x +\n"
    "                     2.0 * C2 * L1m1 * vs_normal.y +\n"
    "                     2.0 * C2 * L10 * vs_normal.z;\n"
    "    vec4 color1 = texture(tex, vs_texCoord);\n"
    "    scattered *= 0.8;\n"
    "    vec3 color2 = min(color1.rgb * scattered, vec3(1.0));\n"
    "    fs_color = vec4(color2, color1.a);\n"
    "}\n";
    
    SphericalHarmonicsFragmentShader::SphericalHarmonicsFragmentShader() :
    FragmentShaderPNT(Imp::code), _m(new Imp)
    {
    }
    
    SphericalHarmonicsFragmentShader::~SphericalHarmonicsFragmentShader()
    {
    }
    
    void SphericalHarmonicsFragmentShader::preDraw(SurfacePNT* surface)
    {
        FragmentShaderPNT::preDraw(surface);
        
        if (TextureUbyte* texture = surface->texture())
            texture->bind();
    }
    
}


