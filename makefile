CC		= gcc
CFLAGS	= -O2
OBJ		= bf.o

build:	bf.c
		$(CC) bf.c -o bf

debug: bf.c
		$(CC) bf.c -g -o bf

default:
	build