/*
 * File-Name: lhp_line.c
 * File-Desc: line buffer services for lh_parse
 * App-Name: lh_parser
 * Project-Name: Las-Header-Parser
 * Copyright: Copyright (c) 2020, DC Slagel
 * License-Identifier: MIT
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // strlen()
#include <ctype.h> // iscntrl(), isspace()

#include "lhp_line.h"

static void lhp_clean_eol(struct LhpLine* lhpline);

// --------------------------------------------------------
// API functions
// --------------------------------------------------------
// struct LhpLine* lhp_line_init(void) {
void lhp_line_init(struct LhpLine* lhpline) {
  lhpline->size = 2048;
  lhpline->line = malloc(lhpline->size);
  lhpline->idx = 0;
}

void lhp_line_config(struct LhpLine* lhpline) {
  lhpline->idx = 0;
  lhp_clean_eol(lhpline);

  // Skip spaces at the beginning of the string.
  while (isspace(lhpline->line[lhpline->idx])) {
    lhpline->idx++;
  }
}

// --------------------------------------------------------
// Internal functions
// --------------------------------------------------------
static void lhp_clean_eol(struct LhpLine* lhpline)
{
    // Remove spaces and new-lines from the end of the line
    size_t line_len = strlen(lhpline->line);
    for (size_t idx = line_len ; idx >= 1; idx--) {
        if (iscntrl(lhpline->line[idx]) || isspace(lhpline->line[idx])) {
            lhpline->line[idx] = '\0';
        }
        else {
            break;
        }
    }
}
