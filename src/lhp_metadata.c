/*
 * File-Name: lhp_line.c
 * File-Desc: line buffer services for lh_parse
 * App-Name: lh_parser
 * Project-Name: Las-Header-Parser
 * Copyright: Copyright (c) 2020, DC Slagel
 * License-Identifier: MIT
 */

#include <ctype.h> // iscntrl(), isspace()
#include <stdbool.h> // true, false
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // strlen()

#include "lhp_metadata.h"
#include "lhp_line.h"

//-------------------------------------------------------------------
// module internal variables : start
//-------------------------------------------------------------------
// Structure for parsing LAS fields: mnemonic_name, unit, value, desc
struct field {
  size_t idx;
  char* buf;
};

//-------------------------------------------------------------------
// module internal variables : finis
//-------------------------------------------------------------------

//-------------------------------------------------------------------
// module internal functions : start
//-------------------------------------------------------------------
static void parse_mnemonic_name(struct field*, struct LhpLine*);
static void parse_unit(struct field*, struct LhpLine*);
static void parse_value(struct field*, struct LhpLine*);
static void parse_desc(struct field*, struct LhpLine*);
//-------------------------------------------------------------------
// module internal functions : finis */
//-------------------------------------------------------------------

//-------------------------------------------------------------------
// API: public-functions
//-------------------------------------------------------------------
struct LhpMetadata* lhp_metadata_init(size_t filesize)
{
  size_t arraysize = 0;
  const size_t estimated_average_bytes_per_line = 55;

  arraysize = filesize / estimated_average_bytes_per_line;
  // printf("ARRAY-SIZE: [%zu]\n", arraysize);

  struct LhpMetadata* lhp_metadata = NULL;
  lhp_metadata = calloc(arraysize, sizeof(struct LhpMetadata));

  if (!lhp_metadata) {
    perror("calloc");
    fprintf(stderr, "error: virtual memory exhausted: Unable to create lhp_metadata.\n");
    exit(EXIT_FAILURE);
  }

  return(lhp_metadata);
}

void lhp_data_init(struct LhpData* lhpdata, size_t filesize)
{
  static const size_t estimated_average_bytes_per_line = 55;

  lhpdata->len = filesize / estimated_average_bytes_per_line;
  // printf("ARRAY-SIZE: [%zu]\n", lhpdata->len);

  lhpdata->array = calloc(lhpdata->len, sizeof(struct LhpMetadata));

  if (!lhpdata->array) {
    perror("calloc");
    fprintf(stderr, "error: virtual memory exhausted: Unable to create lhp_metadata.\n");
    exit(EXIT_FAILURE);
  }
}
/*
void parse_data_line(struct LhpMetadata* lhp_metadata, struct LhpLine* lhpline)
{
    parse_mnemonic_name(lhp_metadata, lhpline);
    parse_unit(lhp_metadata, line);
    parse_value(lhp_metadata, line);
    parse_desc(lhp_metadata, line);
}
*/

void parse_data_line(struct LhpMetadata* lhp_metadata, struct LhpLine* lhpline)
{
    struct field fld;
    char* tofree;
    tofree = fld.buf = strdup(lhpline->line);
    enum fields { mnemonic_name, unit, value, desc, fields_end };

    for (unsigned idx = 0; idx < fields_end; idx++) {
      fld.idx = 0;

      // parse_mnemonic_name(...)

      if (idx == mnemonic_name) {
        parse_mnemonic_name(&fld, lhpline);
      }
      else if (idx == unit) {
        parse_unit(&fld, lhpline);
      }
      else if (idx == value) {
        parse_value(&fld, lhpline);
      }
      else if (idx == desc) {
        parse_desc(&fld, lhpline);
      }

      // Move lhpline->idx past the '.' delimiter.
      lhpline->idx++;

      fld.buf[fld.idx] = '\0';

      // TODO: trim non-unit fields

      // Copy buffer to metadata record field for the current field
      if (idx == mnemonic_name) {
        lhp_metadata->mnemonic_name = strdup(fld.buf);
      }
      else if (idx == unit) {
        lhp_metadata->unit = strdup(fld.buf);
      }
      else if (idx == value) {
        lhp_metadata->value = strdup(fld.buf);
      }
      else if (idx == desc) {
        lhp_metadata->desc = strdup(fld.buf);
      }
    }

    free(tofree);
}

// --------------------------------------------------------
// Internal functions
// --------------------------------------------------------
static void parse_mnemonic_name(struct field* fld, struct LhpLine* lhpline)
{
    while (lhpline->line[lhpline->idx] != '.') {
      fld->buf[fld->idx] = lhpline->line[lhpline->idx];
      lhpline->idx++;
      fld->idx++;
    }
}


static void parse_unit(struct field* fld, struct LhpLine* lhpline)
{
    while (isspace(lhpline->line[lhpline->idx]) == false) {
      fld->buf[fld->idx] = lhpline->line[lhpline->idx];
      lhpline->idx++;
      fld->idx++;
    }
}


static void parse_value(struct field* fld, struct LhpLine* lhpline)
{
    while (lhpline->line[lhpline->idx] != ':') {
      fld->buf[fld->idx] = lhpline->line[lhpline->idx];
      lhpline->idx++;
      fld->idx++;
    }
}


static void parse_desc(struct field* fld, struct LhpLine* lhpline)
{
    while (lhpline->line[lhpline->idx] != '\0') {
      fld->buf[fld->idx] = lhpline->line[lhpline->idx];
      lhpline->idx++;
      fld->idx++;
    }
}

