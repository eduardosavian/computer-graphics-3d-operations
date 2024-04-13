CC = g++
CFLAGS = -lGL -lGLU -lglut -Wall -Wextra -std=c++20 -O2
OPATH = objects
CPATH = src
PROJECT = cgt

.PHONY: all clean

all: $(OPATH) $(PROJECT)

$(OPATH):
	mkdir -p $(OPATH)

cgt: $(OPATH)/main.o $(OPATH)/utils.o
	$(CC) -o cgt $(OPATH)/main.o $(OPATH)/utils.o $(CFLAGS)

$(OPATH)/main.o: $(CPATH)/main.cpp $(CPATH)/utils.hpp
	$(CC) -c -o $(OPATH)/main.o $(CPATH)/main.cpp $(CFLAGS)

$(OPATH)/utils.o: $(CPATH)/utils.cpp $(CPATH)/utils.hpp
	$(CC) -c -o $(OPATH)/utils.o $(CPATH)/utils.cpp $(CFLAGS)

clean:
	rm -rf $(OPATH)/*.o *~ cgt