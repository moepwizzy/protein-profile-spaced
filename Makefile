	# the compiler to use.
CC=g++
# options I'll pass to the compiler.
CFLAGS=-c -Wall# -std=c++0x
LIBFLAGS= -L. -L../threadpool/ -llibsvm_wrapper -lthreadpool -lpthread
LIBS=libthreadpool.a liblibsvm_wrapper.a
TARGETS=class_problem.o profile.o misc.o profile_container.o

all: $(LIBS) $(TARGETS) main.o
	$(CC) main.o $(TARGETS) $(LIBFLAGS) -o test

profile_container.o: profile_container.cpp profile_container.h
	$(CC) $(CFLAGS) profile_container.cpp

class_problem.o: class_problem.cpp class_problem.h
	$(CC) $(CFLAGS) class_problem.cpp

profile.o: profile.cpp profile.h
	$(CC) $(CFLAGS) profile.cpp

misc.o: misc.cpp misc.h
	$(CC) $(CFLAGS) misc.cpp

main.o:  main.cpp
	$(CC) $(CFLAGS) main.cpp

.PHONY: clean
clean:
	rm -rf *.o
	rm -f test
