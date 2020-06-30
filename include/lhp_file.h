/*
 * File-Name: lhp_file.h
 * File-Desc: header file for file services in lhp_file.c
 * App-Name: lh_parser
 * Project-Name: Las-Header-Parser
 * Copyright: Copyright (c) 2020, DC Slagel
 * License-Identifier: MIT
 */


#ifndef LH_FILE_H
#define LH_FILE_H



/* public structs : start */
struct LhpFile {
  FILE *fp;
  size_t size;
};
/* public structs : finis */

/* public-functions */
extern void lhp_file_init(struct LhpFile* lhpfile, const char *lhp_filename);
/* end public-functions */

#endif /* LH_PARSE_H */
