/*
 * File-Name: lhp_section.c
 * File-Desc: LAS section services for lh_parse
 * App-Name: lh_parser
 * Project-Name: Las-Header-Parser
 * Copyright: Copyright (c) 2020, DC Slagel
 * License-Identifier: MIT
 */


#include <stdio.h>  // printf(), exit(), fprintf(), perror()
#include <stdlib.h> // calloc()
#include <string.h> // strncmp(), strdup()

#include "lhp_section.h"

//-------------------------------------------------------------------
// module internal variables : start
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// module internal variables : finis
//-------------------------------------------------------------------

//-------------------------------------------------------------------
// module internal functions : start
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// module internal functions : finis */
//-------------------------------------------------------------------

//-------------------------------------------------------------------
// API: public-functions
//-------------------------------------------------------------------
void lhp_sections_init(struct LhpSections* lhpsections)
{
  // NOTE: 10 is enough for most cases. For now we will just stop registering
  // section header if there are more that 10. Eventually we should allocate
  // more memory for the array when it passes the '10' threashold.
  lhpsections->len = 10;
  lhpsections->idx = 0;

  lhpsections->array = calloc(
      lhpsections->len, sizeof(struct LhpSection));

  if (!lhpsections->array) {
    perror("calloc");
    fprintf(stderr, "error: virtual memory exhausted: Unable to create lhp_sections.\n");
    exit(EXIT_FAILURE);
  }
}


size_t lhp_section_parse(struct LhpSections* lhpsections, char *line, size_t rec_idx)
{
    size_t is_section = 0;

    if (strncmp("~", line, 1) == 0) {

      if (lhpsections->idx == 0 && lhpsections->array[lhpsections->idx].name == NULL)
      {
        lhpsections->array[lhpsections->idx].name = strdup(line);
        lhpsections->array[lhpsections->idx].start_idx = rec_idx;
        lhpsections->array[lhpsections->idx].finis_idx = rec_idx;
        is_section = 1;
      } else if (lhpsections->idx < lhpsections->len) {
        // Update previous sections finishing idx
        lhpsections->array[lhpsections->idx].finis_idx = rec_idx - 1;

        // Initialize the new/current section
        lhpsections->idx++;
        lhpsections->array[lhpsections->idx].name = strdup(line);
        lhpsections->array[lhpsections->idx].start_idx = rec_idx;
        lhpsections->array[lhpsections->idx].finis_idx = rec_idx;
        is_section = 1;
      }
    }

   return(is_section);
}

void display_sections(struct LhpSections* lhpsections)
{
  for (size_t idx = 0; idx <= lhpsections->idx; idx++) {
    printf("#----------------------------------------#\n");
    printf("Section Record: [%zu]\n", idx);
    printf("#----------------------------------------#\n");
    printf("Mnemonic: [%s]\n", lhpsections->array[idx].name);
    printf("Start_idx: [%zu]\n", lhpsections->array[idx].start_idx);
    printf("Finis_idx: [%zu]\n", lhpsections->array[idx].finis_idx);
  }
}

