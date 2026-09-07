CC = gcc
CFLAGS = -Wall -Wextra -std=c11

COMMON = clist.c josephus.c

all: step1 step2

step1: step1.c $(COMMON) clist.h josephus.h
	$(CC) $(CFLAGS) step1.c $(COMMON) -o step1

step2: step2.c $(COMMON) clist.h josephus.h
	$(CC) $(CFLAGS) step2.c $(COMMON) -o step2

clean:
	rm -f step1 step2
