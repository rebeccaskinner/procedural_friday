CC=gcc
LIBNAME=addr_shim.so
SOURCES=$(shell echo *.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))
CFLAGS= -O0 \
	-std=gnu11 \
	-g -ggdb \
	-Wall -Wextra \
	-Wno-unused \
	-fPIC

LFLAGS=-ldl -shared -Wl,--export-dynamic,-soname=$(LIBNAME) -ldl

all: $(LIBNAME) cleanup-bin

$(LIBNAME): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(LIBNAME) $(LFLAGS)

%.o:%.c
	$(CC) -c $(CFLAGS) $(<) -o $(@)

dist-dirs:
	-mkdir -p dist
	-mkdir -p bin

cleanup-bin: dist-dirs
	-mv *.o bin/
	-mv $(LIBNAME) dist/
clean:
	-rm -f *.o
	-rm -f $(LIBNAME)

dist-clean: clean
	-rm -fr bin/

superclean: dist-clean
	-rm -fr dist

.PHONY: all clean

