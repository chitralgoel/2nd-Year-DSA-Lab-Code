JOSEPHUS PROBLEM - CIRCULAR LINKED LIST
==========================================

Files:
    clist.h       Circular linked-list structures and function prototypes
    clist.c       Circular linked-list implementation
    josephus.h    Josephus function prototype
    josephus.c    Josephus wrapper/reuse module
    step1.c       Step 1 client program
    step2.c       Step 2 client program with names
    Makefile      Builds both executables

Compile:
    make

Run Step 1:
    ./step1

Run Step 2:
    ./step2

On Windows using MinGW:
    mingw32-make
    step1.exe
    step2.exe

Important design:
    list.current always represents the node immediately before the
    next person to be counted. locateAndRemove() moves current k-1
    times and then calls removeAfter(). Therefore k=1 works naturally
    without a special-case branch.

Complexity:
    Each removal takes O(k) in the worst case, or O(min(k, current
    list size)) when k is reduced modulo the current size. Since
    there are n-1 removals, the complete simulation is O(n^2) in the
    worst case. The circular linked list uses O(n) memory.
