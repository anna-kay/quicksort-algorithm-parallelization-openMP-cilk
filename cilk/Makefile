
GCC = gcc
CFLAGS = -O3

CMAIN=qsort

all: qsort-main.o qsort-sequential.o qsort-parallel.o 
	$(GCC) -fcilkplus $(CFLAGS) $^ -o $(CMAIN)

%.o: %.c
	$(GCC) -fcilkplus -c $(CFLAGS) $^

clean:
	rm -f *.o *~ $(CMAIN)
