# ------------------------------------------------------------------------------
# Compiler
# ------------------------------------------------------------------------------
CC = clang
CFLAGS = -Wall -Wextra -Weverything -I include

# GCC compiler ------------------------------------------------#
# GNU_VER = 9
# CC   = /usr/local/opt/gcc/bin/gcc-$(GCC_VER)
# COV   = /usr/local/opt/gcc/bin/gcov-$(GCC_VER)
# CFLAGS = -std=c++14 -Wall -Wextra -Wpedantic -pedantic-errors
# GCC compiler ------------------------------------------------#

# ------------------------------------------------------------------------------
# Configure variables
# ------------------------------------------------------------------------------
DEBUG=-g -O0

# f: force removal, v: verbose (list files removed)
RM       = rm -fv

SRCS      = lhp_args.c lhp_parse.c main.c
OBJS      = $(subst .c,.o,$(SRCS))
PRG       = lh_parser
LAS_FILE  = header_line.las

# ------------------------------------------------------------------------------
#  Directory variables
# ------------------------------------------------------------------------------
DIR_DATA = examples
DIR_TEST = build/tests

# ------------------------------------------------------------------------------
#  vpaths
# ------------------------------------------------------------------------------
vpath %.c src
vpath %.h include

# ------------------------------------------------------------------------------
#  PHONEY
# ------------------------------------------------------------------------------
.PHONEY: clean run runtest

# ------------------------------------------------------------------------------
# Make targets
# ------------------------------------------------------------------------------

lh_parser: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

debug: $(OBJS)
	$(CC) $(CFLAGS) $(DEBUG) $^ -o $(PRG)

run:
	./$(PRG) -f $(DIR_DATA)/header_line.las

test: $(DIR_TEST)/test_main

$(DIR_TEST)/test_main: tests/test_main.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I src tests/test_main.c -o $(DIR_TEST)/test_main

runtest:
	$(DIR_TEST)/test_main

clean:
	$(RM) $(OBJS) $(PRG) $(DIR_TEST)/test_main

