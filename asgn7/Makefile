CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic -g
LFLAGS = -lm

all: banhammer adt_testing

banhammer: banhammer.o node.o ll.o ht.o bf.o bv.o speck.o parser.o
	$(CC) -o banhammer $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f banhammer *.o

format:
	clang-format -i -style=file *.h *.c
