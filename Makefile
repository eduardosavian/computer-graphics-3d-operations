CC = g++
CFLAGS = -lGL -lGLU -lglut -Wall -Wextra -std=c++20 -O2
OPATH = objects
CPATH = src
PROJECT = cgt

.PHONY: all clean

all: $(OPATH) $(PROJECT)

$(OPATH):
	mkdir -p $(OPATH)

cgt: $(OPATH)/main.o
	$(CC) -o cgt $(OPATH)/main.o $(CFLAGS)

$(OPATH)/main.o: $(CPATH)/main.cpp
	$(CC) -c -o $(OPATH)/main.o $(CPATH)/main.cpp $(CFLAGS)

clean:
	rm -rf $(OPATH)/*.o *~ cgt