
CC		 := gcc
CFLAGS	 := -Wall -std=c11
CLIBS    :=	-lc -lm
RM       := rm -f

SRCS := test.c vec2.c vec3.c vec4.c mtrx3.c mtrx4.c mtrxC.c qtnn.c
OBJS := $(SRCS:.cpp=.o)

$(info COMMON MAKEFILE)

all: compile link 

compile:
	$(CC) $(FLAGS) -c $(SRCS)

link:
	$(CC) $(OBJS) -o main $(CLIBS)

clean:
	$(RM) *.o
	$(RM) main
