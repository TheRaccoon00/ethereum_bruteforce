all:
	gcc -Wall -o crack crack.c
clean:
	rm crack
	rm results/*
