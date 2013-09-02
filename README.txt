Agl: An OpenGL Library
By Philip M. Hubbard, 2013


Overview

Agl is a C++ library that factors out some code common to setting up and using OpenGL.  Base classes implement simple interactions between shaders, shader programs, surfaces and textures.  Derived classes add details for surfaces and shaders that involve specific types of data, like positions, normals and texture coordinates.  More derived classes define usable shaders for several lighting models.  The library also contains some utilities for managing images.   While the library was designed to be relatively general, it was implemented to meet the needs of the Facetious application.


Implementation

The base classes are Agl::Shader, Agl::ShaderProgram, Agl::Surface and Agl::Texture.  They provide some basic operations common to most applications, like compiling shaders, linking shader programs, storing with a surface its vertex array object for a particular shader program, and avoiding calls to glBindTexture() for a texture that is already bound.  To promote reuse, these classes include few details about the data specific to different types of shaders and surfaces.

The derived classes Agl::SurfacePNT, Agl::VertexShaderPNT and Agl::FragmentShaderPNT add some details specific to surfaces with positions, normals and texture coordinates (the "P", "N" and "T").  The classes use some pure virtual functions that must be redefined by more derived classes; for example, when the shaders initialize the uniform variable for the model-view-projection matrix and the attribute variable for the positions, they use pure virtual functions to get the names of the variables.

The "PNT" classes include enough functionality that there is relatively little code in the more derived classes.  Agl::FlattishRectangularSurface has code to compute the positions, normals and texture coordinates for a tessellated rectangle with an optional curved "bulge".  Agl::BasicVertexShader has the GLSL code for simple viewing transformations, and Agl::PhongOneDirectionalFragmentShader and Agl::SphericalHarmonicsFragmentShader have the GLSL code for two lighting models.

Since the base classes support multiple types of derived surface and shader classes, with different expectations of what data will be present, it is helpful to have some compile-time type checking to ensure that only mutually compatible shaders and surfaces are used together.  Such checking is provided by the Agl::ShaderProgramSpecific template, whose template arguments are a shader type, a fragment-shader type and a surface type.  Agl::ShaderProgramSpecific has API to associate instances of shaders with compatible instances of surfaces, and to draw all the surfaces thus associated.

Agl also contains a few utilities related to images.  Agl::ImagePool avoids repeated allocations of memory for images when one thread is repeatedly producing images and another thread consuming them (as is the pattern in the Facetious application).  The Agl::reduceImageBy2() function reduces the cuts the resolution of an image in half in width and height, and allows the functionality to be applied to a region within the image.

A companion project, AglTest, has confidence tests for (some parts of) Agl.


Building

Agl depends on the Imath library from the IlmBase part of the OpenEXR project.  This code is available on Github or from http://www.openexr.com/downloads.html.

Agl was developed in Xcode (specifically, version 4.6.3). The Xcode project build settings assume that Imath has been installed with header files in /usr/local/include and libraries in /usr/local/lib.  In the "Build Settings," the "Header Search Paths" is set to "/usr/local/include", allowing source code to have include statements like the following:

	#include <OpenEXR/ImathMatrix.h>


Future Work

* 
