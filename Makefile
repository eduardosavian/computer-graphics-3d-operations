CC = clang++
CFLAGS = -lGL -lGLU -lglut -Wall -Wextra -std=c++23 -O2
OPATH = objects
CPATH = src
PROJECT = cgt

.PHONY: all clean

all: cgt

cgt: $(OPATH)/main.o $(OPATH)/utils.o $(OPATH)/polygon.o $(OPATH)/solid.o
	$(CC) -o cgt $(OPATH)/main.o $(OPATH)/utils.o $(OPATH)/polygon.o $(OPATH)/solid.o $(CFLAGS)

$(OPATH)/main.o: $(CPATH)/main.cpp $(CPATH)/utils.hpp $(CPATH)/polygon.hpp $(CPATH)/solid.hpp
	$(CC) -c -o $(OPATH)/main.o $(CPATH)/main.cpp $(CFLAGS)

$(OPATH)/utils.o: $(CPATH)/utils.cpp $(CPATH)/utils.hpp
	$(CC) -c -o $(OPATH)/utils.o $(CPATH)/utils.cpp $(CFLAGS)

$(OPATH)/polygon.o: $(CPATH)/polygon.cpp $(CPATH)/polygon.hpp
	$(CC) -c -o $(OPATH)/polygon.o $(CPATH)/polygon.cpp $(CFLAGS)

$(OPATH)/solid.o: $(CPATH)/solid.cpp $(CPATH)/solid.hpp
	$(CC) -c -o $(OPATH)/solid.o $(CPATH)/solid.cpp $(CFLAGS)

clean:
	rm -rf $(OPATH)/*.o *~ cgt