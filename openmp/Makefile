
GCC = gcc
CFLAGS = -O3

CMAIN=qsort

all: qsort-main.o qsort-parallel.o
	$(GCC) -fopenmp $(CFLAGS) $^ -o $(CMAIN)

%.o: %.c
	$(GCC) -fopenmp -c $(CFLAGS) $^

clean:
	rm -f *.o *~ $(CMAIN)
