# ------------------------------------------------------------------------------
# Clang Compiler
# ------------------------------------------------------------------------------
# CC = clang
# CFLAGS = -Wall -Wextra -Weverything -I include

# ------------------------------------------------------------------------------
# GCC Compiler
# ------------------------------------------------------------------------------
GCC_VER = 9
CC   = /usr/local/opt/gcc/bin/gcc-$(GCC_VER)
COV   = /usr/local/opt/gcc/bin/gcov-$(GCC_VER)
CFLAGS = -Wall -Wextra -Wpedantic -pedantic-errors -I include


# ------------------------------------------------------------------------------
# Compiler variables
# ------------------------------------------------------------------------------
DEBUG=-g -O0

# ------------------------------------------------------------------------------
# Tool variables
# ------------------------------------------------------------------------------
# f: force removal, v: verbose (list files removed)
RM = rm -fv
#
# ------------------------------------------------------------------------------
# Project variables
# ------------------------------------------------------------------------------
PRG       = lh_parser
SRCS      = lhp_args.c lhp_parse.c main.c
OBJS      = $(subst .c,.o,$(SRCS))
LAS_FILE  = ver_line_30.las


# ------------------------------------------------------------------------------
#  Directory variables
# ------------------------------------------------------------------------------
DIR_DATA = examples
DIR_TEST = build/tests
DIR_DEV  = build/dev
DIR_REL  = build/rel
DIR_BIN  = bin

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
# Make development targets
# ------------------------------------------------------------------------------
$(PRG)_dev : $(DIR_DEV)/lh_parser

$(DIR_DEV)/$(PRG): $(SRCS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(DEBUG) $^ -o $(DIR_DEV)/lh_parser

run_dev:
	./$(DIR_DEV)/$(PRG) -f $(DIR_DATA)/3.0/$(LAS_FILE)

clean_dev:
	$(RM) $(OBJS) $(DIR_DEV)/$(PRG)

# ------------------------------------------------------------------------------
# Make test targets
# ------------------------------------------------------------------------------
test: $(DIR_TEST)/test_main

$(DIR_TEST)/test_main: tests/test_main.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I src tests/test_main.c -o $(DIR_TEST)/test_main

run_test:
	$(DIR_TEST)/test_main

clean_test:
	$(RM) $(OBJS) $(PRG) $(DIR_TEST)/test_main


# ------------------------------------------------------------------------------
# General projet mainenance targets
# ------------------------------------------------------------------------------
main.o: src/main.c include/lhp.h include/lhp_args.h include/lhp_parse.h

depends:
	$(CC) $(CFLAGS) -E -MM src/main.c > .depends

clean:
	$(RM) $(OBJS)
	$(RM) -r $(DIR_TEST) $(DIR_DEV)
