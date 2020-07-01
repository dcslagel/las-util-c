# ------------------------------------------------------------------------------
# Clang Compiler
# ------------------------------------------------------------------------------
# CC = clang
# CFLAGS = -Wall -Wextra -Weverything -I include

# ------------------------------------------------------------------------------
# GCC Compiler
# ------------------------------------------------------------------------------
GCC_VER = 9
CC      = /usr/local/opt/gcc/bin/gcc-$(GCC_VER)
COV     = /usr/local/opt/gcc/bin/gcov-$(GCC_VER)
CFLAGS  = -Wall -Wextra -Wpedantic -pedantic-errors -I include
# CFLAGS  = -Wall -Wextra -Wpedantic -Werror -pedantic-errors -I include
# Check memory issues
# CFLAGS  = -Wall -Wextra -Wpedantic -pedantic-errors -fsanitize=address -g -O0 -I include


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
SRCS      = lhp_args.c lhp_file.c lhp_line.c lhp_metadata.c lhp_parse.c
MAIN_SRCS = $(SRCS) main.c
TEST_SRCS = $(SRCS) tests/lhp_test_parse.c tests/test_main.c
MAIN_OBJS      = $(subst .c,.o,$(MAIN_SRCS))
TEST_OBJS      = $(subst .c,.o,$(TEST_SRCS))
LAS_FILE  = dev_example_30.las


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
# Make release targets
# ------------------------------------------------------------------------------
all: $(PRG)

$(PRG) : $(DIR_REL)/$(PRG)

$(DIR_REL)/$(PRG): $(MAIN_SRCS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $^ -o $(DIR_REL)/$(PRG)

run_rel:
	@echo "#----------------------------------------#"
	@echo "LAS_FILE: [$(LAS_FILE)]"
	@echo "#----------------------------------------#"
	./$(DIR_REL)/$(PRG) -f $(DIR_DATA)/3.0/$(LAS_FILE)

clean_rel:
	$(RM) $(OBJS) $(DIR_REL)/$(PRG)

# ------------------------------------------------------------------------------
# Make development targets
# ------------------------------------------------------------------------------
$(PRG)_dev : $(DIR_DEV)/lh_parser

$(DIR_DEV)/$(PRG): $(MAIN_SRCS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(DEBUG) $^ -o $(DIR_DEV)/lh_parser

run_dev:
	./$(DIR_DEV)/$(PRG) -f $(DIR_DATA)/3.0/$(LAS_FILE)

clean_dev:
	$(RM) $(OBJS) $(DIR_DEV)/$(PRG)


# ------------------------------------------------------------------------------
# Make install to bin dir
# ------------------------------------------------------------------------------
install: $(PRG)
	@mkdir -p $(DIR_BIN)
	cp -v $(DIR_REL)/$(PRG) $(DIR_BIN)
	chmod -R og-x $(DIR_BIN)

# ------------------------------------------------------------------------------
# Make test targets
# ------------------------------------------------------------------------------
test: $(DIR_TEST)/test_main

$(DIR_TEST)/test_main: $(TEST_SRCS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I src $^ -o $(DIR_TEST)/test_main

run_test:
	$(DIR_TEST)/test_main

clean_test:
	$(RM) $(OBJS) $(PRG) $(DIR_TEST)/test_main


# ------------------------------------------------------------------------------
# General project maintenance targets
# ------------------------------------------------------------------------------
clean:
	$(RM) $(OBJS)
	$(RM) -r $(DIR_TEST) $(DIR_DEV) $(DIR_REL) $(DIR_BIN)

# ------------------------------------------------------------------------------
#  PHONEY
# ------------------------------------------------------------------------------
.PHONEY: clean make_depends run runtest


# ------------------------------------------------------------------------------
#  Dependency targets
# ------------------------------------------------------------------------------
make_depends: $(SRCS)
	$(CC) $(CFLAGS) -E -MM $^ > depends.mk

include depends.mk


# ------------------------------------------------------------------------------
#  Help
# ------------------------------------------------------------------------------
AWK = /usr/bin/awk
SORT = /usr/bin/sort

.PHONEY: help
help:
	@$(MAKE) --print-data-base --question | \
		$(AWK) '/^[^.%][-A-Za-z0-9_]*:/ {print substr($$1, 1, length($$1)-1)}' | \
		$(SORT)
