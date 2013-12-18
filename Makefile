
CC := gcc
CFLAGS := -g -ggdb -Wall

SRC := critbit.c critbit-test.c
OBJS = $(SRC:%.c=%.o)

all: test

test: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -f test a.out $(OBJS)
