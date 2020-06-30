/*
 * File-Name: lhp_file.c
 * File-Desc: file and line services for lh_parser
 * App-Name: lh_parser
 * Project-Name: Las-Header-Parser
 * Copyright: Copyright (c) 2020, DC Slagel
 * License-Identifier: MIT
 */

#include <stdio.h> // FILE, fclose(), fopen(), fprintf(), perror()
#include <stdlib.h> // exit()
#include <errno.h>

#include <string.h> // strerror
#include <sys/stat.h>
#include <sys/types.h>


#include "lhp_file.h"

static FILE *lhp_file_open(const char *lhp_filename);
static off_t lhp_file_get_size(const char *lhp_filename);


// ---------------------------------------------------------------------
// API functions
// ---------------------------------------------------------------------
void lhp_file_init(struct LhpFile* lhpfile, const char *lhp_filename)
{
  lhpfile->fp = lhp_file_open(lhp_filename);
  lhpfile->size = lhp_file_get_size(lhp_filename);
  
  printf("FILESIZE: [%zu]\n", lhpfile->size);
}


// ---------------------------------------------------------------------
// Support functions
// ---------------------------------------------------------------------
static FILE *lhp_file_open(const char *lhp_filename)
{
  FILE *result;
  result = fopen(lhp_filename, "r");

  if (result == NULL)
  {
    fprintf(
      stdout,
      "INFO: could not open '%s' for reading", lhp_filename);
    perror("fopen");
  }
  return result;
}

static off_t lhp_file_get_size(const char *filename) {
  struct stat st;

  if (stat(filename, &st) == 0)
      return st.st_size;

  fprintf(stderr, "Cannot determine size of %s: %s\n",
          filename, strerror(errno));
  exit(EXIT_FAILURE);

  return -1;
}
