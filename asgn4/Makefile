CC = clang
CFLAGS = -Wall -Werror -Wpedantic -Wextra

all: tsp

tsp: tsp.o graph.o stack.o path.o
	$(CC) -o tsp $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f tsp *.o

format:
	clang-format -i -style=file *.h *.c
