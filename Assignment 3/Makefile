CC=gcc
CFLAG=-Wall -ansi -pedantic
SOURCES=cipher.c transpo.c hill.c
EXECUTABLE=$(basename $(SOURCES))

all: $(EXECUTABLE)

$(EXECUTABLE): FORCE
    $(CC) $(CFLAG) $@.c -o $@

clean:
	rm -f $(EXECUTABLE) *.gch

PHONY: clean
FORCE:	
