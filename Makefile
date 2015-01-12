	# the compiler to use.
CC=g++
# options I'll pass to the compiler.
CFLAGS=-c -Wall
LIBFLAGS= -L. -llibsvm_wrapper -lthreadpool

misc.o: misc.cpp misc.h
	$(CC) $(CFLAGS) misc.cpp

test: liblibsvm_wrapper.a libthreadpool.a misc.o main.cpp
	$(CC) $(CFLAGS) main.cpp
	$(CC) main.o misc.o $(LIBFLAGS) -o test

.PHONY: clean
clean:
	rm -rf *.o
	rm -f test
