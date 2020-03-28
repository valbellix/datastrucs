CC=gcc
CFLAGS=-I.

test:
	$(CC) $(CFLAGS) -o test test.c ds/vect.c
