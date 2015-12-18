CC=gcc

SOURCES=$(shell echo *.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))
CFLAGS= -O0 \
	-std=gnu11 \
	-g -ggdb \
	-Wall -Wextra \
	-Wno-unused \
	-I "../our_so/"\

LFLAGS=-L"../our_so/dist/" -lour_so

APPNAME=our_exe

all: $(APPNAME) cleanup-bin

$(APPNAME): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(APPNAME) $(LFLAGS) -Wl,-rpath="../our_so/dist/"

%.o:%.c
	$(CC) -c $(CFLAGS) $(<) -o $(@)

dist-dirs:
	-mkdir -p dist
	-mkdir -p bin

cleanup-bin: dist-dirs
	-mv *.o bin/
	-mv $(APPNAME) dist/
clean:
	-rm -f *.o
	-rm -f $(APPNAME)
	$(MAKE) -C probe clean

dist-clean: clean
	-rm -fr bin/

superclean: dist-clean
	-rm -fr dist

.PHONY: all clean
