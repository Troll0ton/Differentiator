CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=main.cpp backend.cpp lines_handle.cpp input_output.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=backs

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@