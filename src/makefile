CC=clang
CFLAGS=-Wall -Wextra -Weverything

DEBUG=-g -O0
# f: force removal, v: verbose (list files removed)
RM=rm -fv

SRCS=lhp_args.c lhp_parse.c main.c
OBJS=$(subst .c,.o,$(SRCS))
PRG=lh_parser
LAS_FILE=header_line.las

echo: $(SRCS)
	@echo $(SRCS)

lh_parser: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

debug: $(OBJS)
	$(CC) $(CFLAGS) $(DEBUG) $^ -o $(PRG)

tests: test_main.c
	$(CC) $(CFLAGS) test_main.c -o test_main

.PHONEY: clean
clean:
	$(RM) $(OBJS) $(PRG) test_main

.PHONEY: run
run:
	./$(PRG) -f header_line.las
