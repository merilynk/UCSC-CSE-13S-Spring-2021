CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic
LFLAGS = -lm

all: encode decode error entropy

encode: encode.o hamming.o bv.o bm.o helper.o
	$(CC) -o encode $^

decode: decode.o hamming.o bv.o bm.o helper.o
	$(CC) -o decode $^

error: error.o
	$(CC) -o error error.o

entropy: entropy.o
	$(CC) -o entropy entropy.o $(LFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f encode decode error entropy *.o

format:
	clang-format -i -style=file *.h *.c
