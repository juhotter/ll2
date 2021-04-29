CFLAGS = -std=gnu11 -fopenmp -lm -O3

.PHONY: all clean

all: queens queens_parallel

clean:
	$(RM) queens queens_parallel

client: queens.c queens_parallel.c

