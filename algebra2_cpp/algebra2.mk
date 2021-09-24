
CC       := g++
CFLAGS   := -Wall -std=c++17
LIBS 	 := -lstdc++
RM       := rm -f

SRCS := mtrx2.cpp mtrx3.cpp mtrx4.cpp vec2.o vec3.cpp vec4.cpp qtnn.cpp plane.cpp cmplx.cpp
OBJS := $(SRCS:.cpp=.o)

$(info COMMON MAKEFILE)

all: compile

compile: mtrx2.o mtrx3.o mtrx4.o vec2.o vec3.o vec4.o qtnn.o plane.o cmplx.o

mtrx2.o: mtrx2.cpp
	$(CC) $(CFLAGS) -c mtrx2.cpp

mtrx3.o: mtrx3.cpp
	$(CC) $(CFLAGS) -c mtrx3.cpp 

mtrx4.o: mtrx4.cpp
	$(CC) $(CFLAGS) -c mtrx4.cpp 

vec2.o: vec2.cpp
	$(CC) $(CFLAGS) -c vec2.cpp 

vec3.o: vec3.cpp
	$(CC) $(CFLAGS) -c vec3.cpp

vec4.o: vec4.cpp
	$(CC) $(CFLAGS) -c vec4.cpp

qtnn.o: qtnn.cpp
	$(CC) $(CFLAGS) -c qtnn.cpp 

plane.o: plane.cpp
	$(CC) $(CFLAGS) -c plane.cpp

cmplx.o: cmplx.cpp
	$(CC) $(CFLAGS) -c cmplx.cpp
