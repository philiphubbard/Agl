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
//  AglShader.cpp
//

#include "AglPhongOneDirectionalFragmentShader.h"
#include "AglShaderProgram.h"
#include "AglSurfacePNT.h"
#include "AglTextureUbyte.h"
#include <assert.h>

namespace Agl
{
        
    class PhongOneDirectionalFragmentShader::Imp
    {
    public:
        static const char*  text;
        
        Imath::V3f          ambientColor;
        Imath::V3f          lightColor;
        Imath::V3f          lightDirection;
        GLfloat             shininess;
        GLfloat             strength;
        
        GLint               ambientColorUniform;
        GLint               lightColorUniform;
        GLint               lightDirectionUniform;
        GLint               halfVectorUniform;
        GLint               shininessUniform;
        GLint               strengthUniform;
    };
    
    const char* PhongOneDirectionalFragmentShader::Imp::text =
    "#version 150\n"
    "uniform sampler2D tex;\n"
    "uniform vec3 ambient;\n"
    "uniform vec3 lightColor;\n"
    "uniform vec3 lightDirection;\n"
    "uniform vec3 halfVector;\n"
    "uniform float shininess;\n"
    "uniform float strength;\n"
    "in vec2 vs_texCoord;\n"
    "in vec3 vs_normal;\n"
    "out vec4 fs_color;\n"
    "void main()\n"
    "{\n"
    "    float diffuse = max(0.0, dot(vs_normal, lightDirection));\n"
    "    float specular = max(0.0, dot(vs_normal, halfVector));\n"
    "    if (diffuse == 0.0)\n"
    "        specular = 0.0;\n"
    "    else\n"
    "        specular = pow(specular, shininess);\n"
    "    vec3 scattered = ambient + lightColor * diffuse;\n"
    "    vec3 reflected = lightColor * specular * strength;\n"
    "    vec4 color1 = texture(tex, vs_texCoord);\n"
    "    vec3 color2 = min(color1.rgb * scattered + reflected, vec3(1.0));\n"
    "    fs_color = vec4(color2, color1.a);\n"
    "}\n";
    
    PhongOneDirectionalFragmentShader::PhongOneDirectionalFragmentShader() :
    FragmentShaderPNT(Imp::text), _m(new Imp)
    {
        // Defaults.
        
        _m->ambientColor = Imath::V3f(0.3f, 0.3f, 0.3f);
        _m->lightColor = Imath::V3f(0.6f, 0.6f, 0.6f);
        _m->lightDirection = Imath::V3f(1.0f, 1.0f, 1.0f).normalized();
        _m->shininess = 20.0f;
        _m->strength = 1.0f;
    }
    
    PhongOneDirectionalFragmentShader::~PhongOneDirectionalFragmentShader()
    {
    }
    
    void PhongOneDirectionalFragmentShader::setAmbientColor(const Imath::V3f& v)
    {
        _m->ambientColor = v;
    }
    
    Imath::V3f PhongOneDirectionalFragmentShader::ambientColor() const
    {
        return _m->ambientColor;
    }
    
    Imath::V3f PhongOneDirectionalFragmentShader::lightColor() const
    {
        return _m->lightColor;
    }
    
    void PhongOneDirectionalFragmentShader::setLightColor(const Imath::V3f& v)
    {
        _m->lightColor = v;
    }
    
    void PhongOneDirectionalFragmentShader::setLightDirection(const Imath::V3f& v)
    {
        _m->lightDirection = v;
    }
    
    Imath::V3f PhongOneDirectionalFragmentShader::lightDirection() const
    {
        return _m->lightDirection;
    }
    
    void PhongOneDirectionalFragmentShader::setShininess(GLfloat v)
    {
        _m->shininess = v;
    }
    
    GLfloat PhongOneDirectionalFragmentShader::shininess() const
    {
        return _m->shininess;
    }
    
    void PhongOneDirectionalFragmentShader::setStrength(GLfloat v)
    {
        _m->strength = v;
    }
    
    GLfloat PhongOneDirectionalFragmentShader::strength() const
    {
        return _m->strength;
    }
    
    void PhongOneDirectionalFragmentShader::postLink()
    {
        FragmentShaderPNT::postLink();
        
        _m->ambientColorUniform = glGetUniformLocation(shaderProgram()->id(), "ambient");
        _m->lightColorUniform = glGetUniformLocation(shaderProgram()->id(), "lightColor");
        _m->lightDirectionUniform = glGetUniformLocation(shaderProgram()->id(), "lightDirection");
        _m->halfVectorUniform = glGetUniformLocation(shaderProgram()->id(), "halfVector");
        _m->shininessUniform = glGetUniformLocation(shaderProgram()->id(), "shininess");
        _m->strengthUniform = glGetUniformLocation(shaderProgram()->id(), "strength");
        
        // Use assertions rather than exceptions here because the shader text
        // not set by the caller.
        
        assert(_m->ambientColorUniform >= 0);
        assert(_m->lightColorUniform >= 0);
        assert(_m->lightDirectionUniform >= 0);
        assert(_m->halfVectorUniform >= 0);
        assert(_m->shininessUniform >= 0);
        assert(_m->strengthUniform >= 0);
    }
    
    void PhongOneDirectionalFragmentShader::preDraw()
    {
        FragmentShaderPNT::preDraw();
        
        Imath::V3f halfVector = (Imath::V3f(0.0f, 0.0f, 1.0f) + _m->lightDirection).normalized();
        
        glUniform3fv(_m->ambientColorUniform, 1, _m->ambientColor.getValue());
        glUniform3fv(_m->lightColorUniform, 1, _m->lightColor.getValue());
        glUniform3fv(_m->lightDirectionUniform, 1, _m->lightDirection.getValue());
        glUniform3fv(_m->halfVectorUniform, 1, halfVector.getValue());
        glUniform1f(_m->shininessUniform, _m->shininess);
        glUniform1f(_m->strengthUniform, _m->strength);
    }
    
    void PhongOneDirectionalFragmentShader::preDraw(SurfacePNT* surface)
    {
        FragmentShaderPNT::preDraw(surface);
        
        if (TextureUbyte* texture = surface->texture())
            texture->bind();
    }

}


