CC = clang++
CFLAGS = -lGL -lGLU -lglut -Wall -Wextra -std=c++23 -O2
OPATH = objects
CPATH = src
PROJECT = cgt

.PHONY: all clean

all: cgt

cgt: main.o polygons.o solids.o
	$(CC) -o cgt $(OPATH)/main.o $(OPATH)/polygons.o solids.o $(CFLAGS)

main.o: $(CPATH)/main.cpp $(CPATH)/polygons.hpp  $(CPATH)/polygons.hpp
	$(CC) -c -o $(OPATH)/main.o $(CPATH)/main.cpp $(CFLAGS)

polygons.o: $(CPATH)/polygons.cpp $(CPATH)/polygons.hpp
	$(CC) -c -o $(OPATH)/polygons.o $(CPATH)/polygons.cpp $(CFLAGS)

solids.o: $(CPATH)/solids.cpp $(CPATH)/solids.hpp $(CC) -c -o $(OPATH)/solids.o $(CPATH)/solids.cpp $(CFLAGS)
	$(CC) -c -o $(OPATH)/solids.o $(CPATH)/solids.cpp $(CFLAGS)

clean:
	rm -rf $(OPATH)/*.o *~ cgt
