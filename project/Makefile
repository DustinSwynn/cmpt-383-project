CC=gcc
CFLAGS=-c
LDFLAGS=-lm -lz


convert: convert.o
	$(CC) convert.o -o convert

convert.o: convert.c
	$(CC) $(CFLAGS) convert.c

compress: compress.o
	$(CC) compress.o -o compress $(LDFLAGS)

compress.o: compress.c
	$(CC) $(CFLAGS) compress.c

clean:
	rm *.o convert compress