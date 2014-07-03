
#include <GL/glew.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdexcept>
#include <iostream>

#include "GLHelper.h"

using namespace PlayOpenGL;

// calls glut functions to handle native window creation
void GLHelper::initGlutAndCreateWindow(int argc, char ** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
   glutInitWindowPosition(100, 100);
   glutInitWindowSize(500, 500);
   glutCreateWindow("Triangle");
}


// calls glew init to setup OpenGL version
void GLHelper::initGlew()
{
   GLenum glewStatus = glewInit();
   if (glewStatus != GLEW_OK)
   {
      throw std::runtime_error("glew did not initialize properly");
   }
}


// compiles a shader, any type
// if error compiling then prints an error msg and throws an exception
GLint GLHelper::compileShader(const char * shaderSource, GLenum shaderType)
{
   GLint shader = glCreateShader(shaderType);
   glShaderSource(shader, 1, &shaderSource, NULL);
   glCompileShader(shader);

   GLint compileStatus = GL_FALSE;
   glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
   if (compileStatus == 0)
   {
      int loglen;
      char logbuffer[1000];
      glGetShaderInfoLog(shader, sizeof(logbuffer), &loglen, logbuffer);
      if (loglen > 0)
      {
         std::cout << "error compiling shader. Got info: " << std::endl;
         std::cout << logbuffer << std::endl;
      }
      throw std::runtime_error("error compiling shader");
   }

   return shader;
}

// creates a program and link shaders into the program
// could make this more general purpose by accepting a array/vector of shaders, but keep
// it simple for now
GLuint GLHelper::linkProgram(GLint vertexShader, GLint fragmentShader)
{
   // create program and link shaders
   GLuint program = glCreateProgram();
   glAttachShader(program, vertexShader);
   glAttachShader(program, fragmentShader);
   glLinkProgram(program);

   GLint linkStatus;
   glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
   if (! linkStatus)
   {
      throw std::runtime_error("error linking");
   }

   return program;
}


// gets attribute location/handle. attributeName must match variable name used in a shader
GLint GLHelper::getAttributeLocation(GLuint program, const char * attributeName)
{
   GLint attributeLocation = glGetAttribLocation(program, attributeName);
   if (attributeLocation == -1)
   {
      throw std::runtime_error("error specifying attribute name");
   }
   return attributeLocation;
}

