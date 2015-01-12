	# the compiler to use.
CC=g++
# options I'll pass to the compiler.
CFLAGS=-c -Wall
LIBFLAGS= -L. -llibsvm_wrapper -lthreadpool
LIBS=libthreadpool.a liblibsvm_wrapper.a

profile.o: profile.cpp profile.h
	$(CC) $(CFLAGS) profile.cpp

misc.o: misc.cpp misc.h
	$(CC) $(CFLAGS) misc.cpp

test: $(LIBS) profile.o misc.o main.cpp
	$(CC) $(CFLAGS) main.cpp
	$(CC) main.o misc.o $(LIBFLAGS) -o test

.PHONY: clean
clean:
	rm -rf *.o
	rm -f test
