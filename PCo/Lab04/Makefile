PROJECT=router
SOURCES=router.c skel.c
LIBRARY=nope
INCPATHS=.
LIBPATHS=.
LDFLAGS=
CFLAGS=-c -Wall
CC=gcc

# ------------ MAGIC BEGINS HERE -------------

# Automatic generation of some important lists
OBJECTS=$(SOURCES:.c=.o) parser.o
INCFLAGS=$(foreach TMP,$(INCPATHS),-I$(TMP))
LIBFLAGS=$(foreach TMP,$(LIBPATHS),-L$(TMP))

# Set up the output file names for the different output types
BINARY=$(PROJECT)

all: $(SOURCES) $(BINARY)

$(BINARY): $(OBJECTS)
	$(CC) $(LIBFLAGS) $(OBJECTS) $(LDFLAGS) -o $@

.c.o:
	$(CC) $(INCFLAGS) $(CFLAGS) -fPIC $< -o $@

distclean: clean
	rm -f $(BINARY)

clean:
	rm -f router.o skel.o

