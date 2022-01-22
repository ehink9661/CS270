#Ethan Hinkle *** Assignment 4 *** makefile
#CS 270 - Bolden

cc = gcc
cflags = -ansi -Wall -g
tgts = client server


all:
	make client
	make server

CLIENT: client.c
	$(cc) $(cflags) client.c -o client

SERVER: server.c
	$(cc) $(cflags) server.c -o server

clean:
	rm $(tgts)
