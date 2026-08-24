CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -pedantic -O2

all: infixToPostfix

infixToPostfix: infixToPostfix.o stack.o
	$(CC) $(CFLAGS) -o $@ $^

infixToPostfix.o: infixToPostfix.c stack.h
	$(CC) $(CFLAGS) -c $<

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o infixToPostfix
