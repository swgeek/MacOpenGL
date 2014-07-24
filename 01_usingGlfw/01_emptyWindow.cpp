// complile using: 
// g++ 01_emptyWindow.cpp -o 01_emptyWindow -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo -lglfw3
#include <GLFW/glfw3.h>

#include <iostream>

void error_callback(int error, const char * description)
{
   std::cout << "GLFW error <" << error << ">: " << description << std::endl;
}

int main(int argc, char ** argv)
{
   glfwSetErrorCallback(error_callback);

   if (! glfwInit())
      exit(1);

   GLFWwindow * window = glfwCreateWindow(500, 500, "Simple Window", NULL, NULL);

   //glutInitWindowPosition(100, 100);
   if (! window)
   {
      glfwTerminate();
      exit(1);
   }

   glfwMakeContextCurrent(window);

   while (! glfwWindowShouldClose(window))
   {
      // keep running
   }
   glfwDestroyWindow(window);
   glfwTerminate();





}

