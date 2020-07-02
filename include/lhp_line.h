/*
 * File-Name: lhp_line.h
 * File-Desc: header file for line services in lh_parse
 * App-Name: lh_parser
 * Project-Name: Las-Header-Parser
 * Copyright: Copyright (c) 2020, DC Slagel
 * License-Identifier: MIT
 */

#ifndef LHP_LINE_H
#define LHP_LINE_H

#include <stdio.h>

/* public structs : start */
struct LhpLine {
  char *line;
  size_t idx;
  size_t size;
};
/* public structs : finis */

/* public-functions */
extern void lhp_line_init(struct LhpLine* lhpline);
extern void lhp_line_config(struct LhpLine* lhpline);
/* end public-functions */

#endif /* LHP_LINE_H */
