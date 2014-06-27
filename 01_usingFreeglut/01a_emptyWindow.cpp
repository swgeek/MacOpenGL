
// complile using: g++ 01a_emptyWindow.cpp -o 01a_emptyWindow -framework OpenGL -lGLUT

#include <GL/freeglut.h>

void render(void)
{
}

int main(int argc, char ** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
   glutInitWindowPosition(100, 100);
   glutInitWindowSize(500, 500);
   glutCreateWindow("Simple Window");
   glutDisplayFunc(render);
   glutMainLoop();

   return 1;
}

