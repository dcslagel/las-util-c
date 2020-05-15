CC=clang
CFLAGS=-Wall -Wextra -Weverything

DEBUG=-g -O0
# f: force removal, v: verbose (list files removed)
RM=rm -fv

SRCS=*.c
OBJS=$(subst .c,.o,$(SRCS))
PRG=lh_parser

all: *.c
	$(CC) $(CFLAGS) *.c -o $(PRG)

debug: *.c
	$(CC) $(CFLAGS) $(DEBUG) *.c -o $(PRG)


alt: *.c
	$(CC) $(CFLAGS) alt1.c -o alt1.o

.PHONEY: clean
clean:
	$(RM) $(OBJS) $(PRG)

.PHONEY: run
run:
	./$(PRG)
