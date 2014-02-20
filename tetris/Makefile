#! /usr/bin/make

# Generic Makefile that should work with any program you're going to compile.
# Any complaints should be directed at honghual@sfu.ca
#
# To compile and link your program all you have to do is run 'make' in the
#    current directory.
# To clean up object files run 'make clean_object'.
# To delete any compiled files run 'make clean'.
# Originated in 2001 by Haris Teguh
# modified May-2012 by Honghua Li

# Including of non standard library files:
#   INCLUDEDIR is where the header files can be found
#   LIBDIR is where the library object files can be found
INCLUDEDIR=/usr/include/
LIBDIR=/usr/lib

# If you have more source files add them here
SOURCE= Tetris.cpp Game.cpp Board.cpp Tetromino.cpp include/InitShader.cpp

# The compiler we are using
CC= g++

# The name of the final executable
EXECUTABLE= tetris

# Linux (default)
CFLAGS= -O0 -g -Wall -pedantic -Wno-unused-result -DGL_GLEXT_PROTOTYPES
LDFLAGS= -lGL -lglut -lGLEW -lXext -lX11 -lm

# OS X
# CFLAGS= -O3 -g -Wall -pedantic -std=gnu++11 -Wno-deprecated-declarations -DGL_GLEXT_PROTOTYPES
# LDFLAGS = -framework OpenGL -framework GLUT

# If you have other library files in a different directory add them here
INCLUDEFLAG= -I. -I$(INCLUDEDIR) -Iinclude/
LIBFLAG= -L$(LIBDIR)

# Don't touch this one if you don't know what you're doing
OBJECT= $(SOURCE:.cpp=.o)

# Don't touch any of these either if you don't know what you're doing
all: $(OBJECT) depend
	$(CC) $(CFLAGS) $(INCLUDEFLAG) $(LIBFLAG) $(OBJECT) -o $(EXECUTABLE) $(LDFLAGS)

tetris: all

rebuild: clean all

depend:
	$(CC) -M $(SOURCE) > depend

$(OBJECT):
	$(CC) $(CFLAGS) $(INCLUDEFLAG) -c -o $@ $(@:.o=.cpp)

clean_object:
	rm -f $(OBJECT)

clean:
	rm -f $(OBJECT) depend $(EXECUTABLE)

include depend
