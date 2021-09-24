
CC       := g++
CFLAGS   := -Wall -std=c++17
LIBS 	 := -lstdc++
RM       := rm -f

SRCS := test.cpp mtrx234.cpp vec234.cpp qtnn.cpp plane.cpp
OBJS := $(SRCS:.cpp=.o)

$(info COMMON MAKEFILE)

all: compile link 

compile: mtrx234.o vec234.o qtnn.o plane.o test.o

mtrx234.o: mtrx234.cpp
	$(CC) $(CFLAGS) -c mtrx234.cpp 

vec234.o: vec234.cpp
	$(CC) $(CFLAGS) -c vec234.cpp 

qtnn.o: qtnn.cpp
	$(CC) $(CFLAGS) -c qtnn.cpp 

plane.o: plane.cpp
	$(CC) $(CFLAGS) -c plane.cpp

test.o: test.cpp
	$(CC) $(CFLAGS) -c test.cpp

link:
	$(CC) $(OBJS) -o main $(LIBS)

clean:
	$(RM) *.o
	$(RM) main
