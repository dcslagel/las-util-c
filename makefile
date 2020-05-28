# ------------------------------------------------------------------------------
# Compiler
# ------------------------------------------------------------------------------
CC = clang
CFLAGS = -Wall -Wextra -Weverything -I include

# ------------------------------------------------------------------------------
# Configure variables
# ------------------------------------------------------------------------------
DEBUG=-g -O0

# f: force removal, v: verbose (list files removed)
RM=rm -fv

SRCS=lhp_args.c lhp_parse.c main.c
OBJS=$(subst .c,.o,$(SRCS))
PRG=lh_parser
LAS_FILE=header_line.las

# ------------------------------------------------------------------------------
#  Directory variables
# ------------------------------------------------------------------------------
EXAMPLE_DATA = examples

# ------------------------------------------------------------------------------
#  vpaths
# ------------------------------------------------------------------------------
vpath %.c src
vpath %.h include

# ------------------------------------------------------------------------------
# Make targets
# ------------------------------------------------------------------------------

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
	./$(PRG) -f $(EXAMPLE_DATA)/header_line.las
