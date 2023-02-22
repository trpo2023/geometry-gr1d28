all: a.out

a.out: geometry1.c
	gcc -Wall -Werror geometry1.c

