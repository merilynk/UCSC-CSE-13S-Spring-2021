CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic
LFLAGS = -lm

all: sorting

sorting: sorting.o bubble.o shell.o quick.o stack.o queue.o set.o helper.o
	$(CC) -o sorting sorting.o bubble.o shell.o quick.o stack.o queue.o set.o helper.o $(LFLAGS)

sorting.o: sorting.c
	$(CC) $(CFLAGS) -c sorting.c

bubble.o: bubble.c
	$(CC) $(CFLAGS) -c bubble.c

gaps.o: gaps.c
	$(CC) $(CFLAGS) -c gaps.c

shell.o: shell.c
	$(CC) $(CFLAGS) -c shell.c

quick.o: quick.c
	$(CC) $(CFLAGS) -c quick.c

stack.o: stack.c
	$(CC) $(CFLAGS) -c stack.c

queue.o: queue.c
	$(CC) $(CFLAGS) -c queue.c

set.o: set.c
	$(CC) $(CFLAGS) -c set.c

clean:
	rm -f *.o sorting

format:
	clang-format -i -style=file *.h *.c
