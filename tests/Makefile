IDIR =../src
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=../src
LDIR =../src

LIBS=-lm

_DEPS = minunit.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = hamt.o ../tests/main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

hamt_tests: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 

