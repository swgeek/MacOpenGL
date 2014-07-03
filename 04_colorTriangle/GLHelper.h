#include <GL/glew.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdexcept>
#include <iostream>

namespace PlayOpenGL
{

class GLHelper
{
public:
   // calls glut functions to handle native window creation
   static void initGlutAndCreateWindow(int argc, char ** argv);

   // calls glew init to setup OpenGL version
   static void initGlew(void);

   // compiles a shader, any type
   // if error compiling then prints an error msg and throws an exception
   static GLint compileShader(const char * shaderSource, GLenum shaderType);

   // creates a program and link shaders into the program
   // could make this more general purpose by accepting a array/vector of shaders, but keep
   // it simple for now
   static GLuint linkProgram(GLint vertexShader, GLint fragmentShader);

   // gets attribute location/handle. attributeName must match variable name used in a shader
   static GLint getAttributeLocation(GLuint program, const char * attributeName);
};

}
