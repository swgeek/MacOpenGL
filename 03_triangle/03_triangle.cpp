// complile using: g++ 03_triangle.cpp -o 03_triangle -framework OpenGL -framework GLUT -lglew
// -w to get rid of warnings

#include <GL/glew.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>

// these need to be globals as need them in render function
GLuint openGLProgramObject;
GLint coordAttribute;

GLuint compileShaders()
{
   // vertex shader and fragment shader programs.    
   const char * vertexShaderSource = "#version 120\n attribute vec2 coord; void main(void) { gl_Position = vec4(coord, 0.0, 1.0); }";
   const char * fragmentShaderSource = "#version 120 \n void main(void) { gl_FragColor[0] = 1.0; gl_FragColor[1] = 1.0; gl_FragColor[2] = 1.0;} ";

   // compile vertex shader 
   GLint vertexShader = glCreateShader(GL_VERTEX_SHADER);
   glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
   glCompileShader(vertexShader);

   GLint compileStatus = GL_FALSE;
   glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compileStatus);
   if (compileStatus == 0)
   {
      std::cout << "error compiling vertex shader: " << vertexShaderSource  << std::endl;
   }

   // compile fragment shader
   GLint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
   glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
   glCompileShader(fragmentShader);
   glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compileStatus);
   if (compileStatus == 0)
   {
      std::cout << "error compiling fragment shader"  << std::endl;
   }

   // link vertex shader and fragment shader into program
   GLuint program = glCreateProgram();
   glAttachShader(program, vertexShader);
   glAttachShader(program, fragmentShader);
   glLinkProgram(program);

   GLint linkStatus;
   glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
   if (! linkStatus)
   {
      // error
      std::cout << "error linking" << std::endl;
   }

   return program;
}

// render is continually called by main loop to render each frame
// cannot pass parameters because of function signature (void), 
// so uses globals: openGLProgramObject, coordAttribute
void render(void)
{
   // clear color buffer to the value set by glClearColor
   glClear(GL_COLOR_BUFFER_BIT);

   glUseProgram(openGLProgramObject);

   // copy vertex data over to the OpenGL side 
   glEnableVertexAttribArray(coordAttribute);
   GLfloat vertices[] = {0, 0.5, -0.5, -0.5, 0.5, -0.5};
   glVertexAttribPointer(coordAttribute, 2, GL_FLOAT, GL_FALSE, 0, vertices);

   // perform the drawing
   glDrawArrays(GL_TRIANGLES, 0, 3);

   // clean up after ourselves, not necessary in a simple program like this, but good habit
   glDisableVertexAttribArray(coordAttribute);

   glutSwapBuffers();
}


int main(int argc, char ** argv)
{
   // initialization
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
   glutInitWindowPosition(100, 100);
   glutInitWindowSize(500, 500);
   glutCreateWindow("Triangle");

   GLenum glewStatus = glewInit();
   if (glewStatus != GLEW_OK)
   {
      std::cout << "glew did not initialize properly" << std::endl;
      return 1;
   } 

   // compile and link shader programs, also sets program global variable
   openGLProgramObject = compileShaders();

   // get location/handle for coord variable in the vertex shader
   const char * attributeName = "coord";
   coordAttribute = glGetAttribLocation(openGLProgramObject, attributeName);
   if (coordAttribute == -1)
   {
      std::cout << "Could not find coord attribute" << std::endl;
      return 1;
   }

   // set the render function to continually call in the main loop
   glutDisplayFunc(render);

   // glClearColor only sets state, does not actually clear anything
   glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

   // done with setup, now constantly loop and call render function
   glutMainLoop();

   return 1;
}

