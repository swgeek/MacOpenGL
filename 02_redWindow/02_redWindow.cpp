
// complile using: g++ 02_redWindow.cpp -o 02_redWindow -framework OpenGL -framework GLUT

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void render(void)
{
   // clear color buffer to the value set by glClearColor
   glClear(GL_COLOR_BUFFER_BIT);

   glutSwapBuffers();
}


int main(int argc, char ** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
   glutInitWindowPosition(100, 100);
   glutInitWindowSize(500, 500);
   glutCreateWindow("Simple Window");
   glutDisplayFunc(render);

   // glClearColor only sets state, does not actually clear anything
   glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

   glutMainLoop();

   return 1;
}

