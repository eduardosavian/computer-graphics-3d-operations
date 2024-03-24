CC = clang++
CFLAGS = -lGL -lGLU -lglut -Wall -Wextra -std=c++23 -O2
OPATH = objects
CPATH = src
PROJECT = cgt

.PHONY: all clean

all: $(OPATH) $(PROJECT)

$(OPATH):
	mkdir -p $(OPATH)

cgt: $(OPATH)/main.o $(OPATH)/utils.o $(OPATH)/cube.o
	$(CC) -o cgt $(OPATH)/main.o $(OPATH)/utils.o $(OPATH)/cube.o $(CFLAGS)

$(OPATH)/main.o: $(CPATH)/main.cpp $(CPATH)/utils.hpp $(CPATH)/cube.hpp
	$(CC) -c -o $(OPATH)/main.o $(CPATH)/main.cpp $(CFLAGS)

$(OPATH)/utils.o: $(CPATH)/utils.cpp $(CPATH)/utils.hpp
	$(CC) -c -o $(OPATH)/utils.o $(CPATH)/utils.cpp $(CFLAGS)

$(OPATH)/cube.o: $(CPATH)/cube.cpp $(CPATH)/cube.hpp
	$(CC) -c -o $(OPATH)/cube.o $(CPATH)/cube.cpp $(CFLAGS)

clean:
	rm -rf $(OPATH)/*.o *~ cgt