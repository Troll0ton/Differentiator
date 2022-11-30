CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=descent.cpp lines_handle.cpp input_output.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=descnt

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@