CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic

all: sorting

sorting: sorting.o bubble.o shell.o quick.o set.o helper.o
	$(CC) $(CFLAGS) -o sorting sorting.o bubble.o shell.o quick.o stack.o queue.o set.o helper.o

sorting.o: sorting.c
	$(CC) $(CFLAGS) -c sorting.c

bubble.o: bubble.c
	$(CC) $(CFLAGS) -c bubble.c

shell.o: shell.c
	$(CC) $(CFLAGS) -c shell.c

quick.o: quick.c
	$(CC) $(CFLAGS) -c quick.c

set.o: set.c
	$(CC) $(CFLAGS) -c set.c

helper.o: helper.c
	$(CC) $(CFLAGS) -c helper.c

clean:
	rm -f *.o sorting

format:
	clang-format -i -style=file *.h *.c
