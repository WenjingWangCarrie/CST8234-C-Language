C=gcc
CFLAGS=-c
GLFLAGS=
SOURCES=Ayala_particles.c Ayala_particle.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=pss

all: $(SOURCES) $(EXECUTABLE) 

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(GLFLAGS) $(OBJECTS) -o $@

.c:.o 
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o $(EXECUTABLE)
