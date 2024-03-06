CC = clang++
CFLAGS = -Wall -Wextra
LDFLAGS = -lGL -lGLU -lglut

all: cgt

cgt: cgt.o
	$(CC) $(CFLAGS) -o cgt cgt.o $(LDFLAGS)

.PHONY: clean

clean:
	rm -f cgt *.o