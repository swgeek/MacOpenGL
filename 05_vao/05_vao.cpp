// complile using: g++ 05_vao.cpp GLHelper.cpp -o 05_vao -framework OpenGL -framework GLUT -lglew
// -w to get rid of warnings

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

// these need to be globals as need them in render function
GLuint openGLProgramObject;
GLint coordAttribute;
GLint colorAttribute;
GLuint vertexBuffer;
GLuint vertexColorBuffer;

// compiles and links vertex and fragment shaders into program
GLuint compileShaders()
{
   // vertex shader
   const char * vertexShaderSource = "#version 120\n attribute vec2 coord; attribute vec4 color; varying vec4 colorOut; void main(void) { gl_Position = vec4(coord, 0.0, 1.0); colorOut = color; }";
   GLint vertexShader = GLHelper::compileShader(vertexShaderSource, GL_VERTEX_SHADER);

   // fragment shader
   const char * fragmentShaderSource = "#version 120 \n varying vec4 colorOut; void main(void) { gl_FragColor = colorOut;} ";
   GLint fragmentShader = GLHelper::compileShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

   // create program and link shaders
   return GLHelper::linkProgram(vertexShader, fragmentShader);
}


// gets attribute location/handle. attributeName must match variable name used in a shader
GLint getAttributeLocation(GLuint program, const char * attributeName)
{
   GLint attributeLocation = glGetAttribLocation(program, attributeName);
   if (attributeLocation == -1)
   {
      throw std::runtime_error("error specifying attribute name");
   }
   return attributeLocation;
}


// render is continually called by main loop to render each frame
// cannot pass parameters because of function signature (void), 
// so uses globals: program, vertices, coordAttribute
void render(void)
{
   // clear color buffer to the value set by glClearColor
   glClear(GL_COLOR_BUFFER_BIT);

   glUseProgram(openGLProgramObject);

   // specify vertex data layout
   glEnableVertexAttribArray(coordAttribute);
   glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
   glVertexAttribPointer(coordAttribute, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);

   // specify vertexColor data layout
   glEnableVertexAttribArray(colorAttribute);
   glBindBuffer(GL_ARRAY_BUFFER, vertexColorBuffer);
   glVertexAttribPointer(colorAttribute, 4, GL_FLOAT, GL_FALSE, 0, (void *)0);

   // perform the drawing
   glDrawArrays(GL_TRIANGLES, 0, 3);

   // clean up after ourselves, not necessary in a simple program like this, but good habit
   glDisableVertexAttribArray(coordAttribute);
   glDisableVertexAttribArray(colorAttribute);

   glutSwapBuffers();
}


int main(int argc, char ** argv)
{
   GLHelper::initGlutAndCreateWindow(argc, argv);
   GLHelper::initGlew();

   // compile and link shader programs, also sets program global variable
   openGLProgramObject = compileShaders();

   // get location/handle for coord variable in the vertex shader
   coordAttribute = GLHelper::getAttributeLocation(openGLProgramObject, "coord");
   colorAttribute = GLHelper::getAttributeLocation(openGLProgramObject, "color");

   // generate a buffer in openGL. vertexBuffer will hold a handle to the buffer.
   // note this does not actually allocate space for the buffer
   glGenBuffers(1, &vertexBuffer);
 
   // make the buffer the current array buffer so we can work with it
   glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

   GLfloat vertices[] = {0, 0.5, -0.5, -0.5, 0.5, -0.5};
   // copy our data over. This will create the actual buffer and copy data to it.
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

   // now do the same steps for vertex color data

   // generate a buffer and make it current array buffer
   glGenBuffers(1, &vertexColorBuffer);
   glBindBuffer(GL_ARRAY_BUFFER, vertexColorBuffer);

   // copy vertex color data over to the OpenGL side 
   GLfloat vertexColors[] = {1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1};
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertexColors), vertexColors, GL_STATIC_DRAW);

   // set the render function to continually call in the main loop
   glutDisplayFunc(render);

   // glClearColor only sets state, does not actually clear anything
   glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

   // done with setup, now constantly loop and call render function
   glutMainLoop();

   return 1;
}

