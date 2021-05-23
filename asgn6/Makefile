CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic
LFLAGS = -lm

all: encode decode entropy

encode: encode.o huffman.o stack.o pq.o node.o code.o io.o
	$(CC) -o encode $^

decode: decode.o huffman.o stack.o pq.o node.o code.o io.o
	$(CC) -o decode $^

entropy: entropy.o
	$(CC) -o entropy entropy.o $(LFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f encode decode entropy *.o

format:
	clang-format -i -style=file *.h *.c
