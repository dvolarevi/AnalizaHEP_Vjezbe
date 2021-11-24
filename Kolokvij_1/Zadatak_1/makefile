CC=g++ --std=c++11
CFLAGS=-I.
DEPS = stat.h

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

analyzer: run.o stat.o
	$(CC) -o run run.o stat.o

clean:
	rm -rf *.o run
