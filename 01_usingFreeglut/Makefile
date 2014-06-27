#OBJS specifies which files to compile as part of the project
OBJS = 01a_emptyWindow.cpp

#compiler to use
CC = g++

INCLUDE_PATHS = -I/usr/local/include -I/opt/X11/include

LIBRARY_PATHS = -L/usr/local/lib -I/opt/X11/lib 

COMPILER_FLAGS = -w

LINKER_FLAGS = -framework OpenGL -lGLUT 

#OBJ_NAME specifies the name of our executable
OBJ_NAME = 01a_emptyWindow

#this is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

