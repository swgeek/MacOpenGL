
// complile using: g++ 01_emptyWindow.cpp -o 01_emptyWindow -framework OpenGL -framework GLUT

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

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

