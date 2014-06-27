// complile using: g++ 03_triangle_v2.cpp -o 03_triangle_v2 -framework OpenGL -framework GLUT -lglew
// -w to get rid of warnings

#include <GL/glew.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdexcept>

// these need to be globals as need them in render function
GLuint openGLProgramObject;
GLint coordAttribute;

// calls glut functions to handle native window creation
void initGlutAndCreateWindow(int argc, char ** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
   glutInitWindowPosition(100, 100);
   glutInitWindowSize(500, 500);
   glutCreateWindow("Triangle");
}


// calls glew init to setup OpenGL version
void initGlew()
{
   GLenum glewStatus = glewInit();
   if (glewStatus != GLEW_OK)
   {
      throw std::runtime_error("glew did not initialize properly");
   }
}


// compiles a shader, any type
GLint compileShader(const char * shaderSource, GLenum shaderType)
{
   GLint shader = glCreateShader(shaderType);
   glShaderSource(shader, 1, &shaderSource, NULL);
   glCompileShader(shader);

   GLint compileStatus = GL_FALSE;
   glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
   if (compileStatus == 0)
   {
      throw std::runtime_error("error compiling shader");
   }

   return shader;
}

// creates a program and link shaders into the program
// could make this more general purpose by accepting a array/vector of shaders, but keep
// it simple for now
GLuint linkProgram(GLint vertexShader, GLint fragmentShader)
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


// compiles and links vertex and fragment shaders into program
GLuint compileShaders()
{
   // vertex shader
   const char * vertexShaderSource = "#version 120\n attribute vec2 coord; void main(void) { gl_Position = vec4(coord, 0.0, 1.0); }";
   GLint vertexShader = compileShader(vertexShaderSource, GL_VERTEX_SHADER);

   // fragment shader
   const char * fragmentShaderSource = "#version 120 \n void main(void) { gl_FragColor[0] = 1.0; gl_FragColor[1] = 1.0; gl_FragColor[2] = 1.0;} ";
   GLint fragmentShader = compileShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

   // create program and link shaders
   return linkProgram(vertexShader, fragmentShader);
}


// gets attribute location/handle. attributeName must match variable name used in a shader
GLint getAttributeLocation(const char * attributeName)
{
   GLint attributeLocation = glGetAttribLocation(openGLProgramObject, attributeName);
   if (coordAttribute == -1)
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
   initGlutAndCreateWindow(argc, argv);
   initGlew();

   // compile and link shader programs, also sets program global variable
   openGLProgramObject = compileShaders();

   // get location/handle for coord variable in the vertex shader
   coordAttribute = getAttributeLocation("coord");

   // set the render function to continually call in the main loop
   glutDisplayFunc(render);

   // glClearColor only sets state, does not actually clear anything
   glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

   // done with setup, now constantly loop and call render function
   glutMainLoop();

   return 1;
}

