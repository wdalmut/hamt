CC=gcc
CFLAGS=-I.
DEPS =
OBJ = hamt.o main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

hamt: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o
