CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

all: encode decode error entropy

encode: encode.o hamming.o bv.o bm.o
	$(CC) -o encode $^

decode: decode.o hamming.o bv.o bm.o
	$(CC) -o decode $^

error: error.o
	$(CC) -o error

entropy: entropy.o
	$(CC) -o entropy

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f encoder decoder error entropy *.o

format:
	clang-format -i style=file *.h *.c
