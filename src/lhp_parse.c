/*
 * File-Name: lhp_parse.c
 * File-Desc: parsing functions in lh_parse
 * App-Name: lh_parser
 * Project-Name: Las-Header-Parser
 * Copyright: Copyright (c) 2020, DC Slagel
 * License-Identifier: MIT
 */

#include <ctype.h> // iscntrl(), isspace()
#include <stdio.h> // FILE, fclose(), fopen(), fprintf(), perror()
#include <stdlib.h> // malloc()
#include <string.h> // strlen(), strncmp(), strncpy(), strdup()


#include "lhp_parse.h"
#include "lhp_file.h"
#include "lhp_line.h"
#include "lhp_metadata.h"

//-------------------------------------------------------------------
// module private variables : start
//-------------------------------------------------------------------
static char *lhp_section_type = NULL;
static size_t rec_idx = 0;
//-------------------------------------------------------------------
// module private variables : finis
//-------------------------------------------------------------------

//-------------------------------------------------------------------
// module private functions : start
//-------------------------------------------------------------------
static void free_records(struct LhpMetadata* lasm_records, size_t lhp_array_size);
static void display_records(struct LhpMetadata* lasm_records);
static size_t parse_section_type(char *line);
//-------------------------------------------------------------------
// module private functions : finis
//-------------------------------------------------------------------


void parse_las_file(const char *lhp_filename)
{
    struct LhpFile lhpfile;
    lhp_file_init(&lhpfile, lhp_filename);

    struct LhpLine lhpline;
    lhp_line_init(&lhpline);

    struct LhpData lhpdata;
    lhp_data_init(&lhpdata, lhpfile.size);

    // Memory: free(lasm_records); when done.
    struct LhpMetadata *lasm_records = lhpdata.array;

    while (fgets(lhpline.line, lhpline.size, lhpfile.fp))
    {
        lhp_line_config(&lhpline);
        if (parse_section_type(lhpline.line)) {
          continue;
        }

        if (strncmp("#", lhpline.line, 1) == 0) {
          continue;
        }

        // ---------------------------------------------------------------------
        // Parse fields for the current line/record
        // ---------------------------------------------------------------------
        parse_data_line(&lasm_records[rec_idx], &lhpline); 

        rec_idx = rec_idx + 1;
    }

    if (fclose(lhpfile.fp) == EOF) {
        perror("close");
    }

    display_records(lasm_records);

    free_records(lasm_records, lhpdata.len);
}

static size_t parse_section_type(char *line)
{
    size_t is_section = 0;

    if (strncmp("~", line, 1) == 0) {
      lhp_section_type = strdup(line);
      is_section = 1;
      printf("Section Type: [%s]\n\n", lhp_section_type);
    }
    return(is_section);
}


void free_records(struct LhpMetadata *lasm_records, size_t lhp_array_size)
{
    // printf("Array Size [%zu]\n", lhp_array_size);
    for (size_t free_idx = 0; free_idx < lhp_array_size; free_idx++) {
        // printf("releasing memory for rec_idx [%ld]\n", free_idx);
        free(lasm_records[free_idx].mnemonic_name);
        free(lasm_records[free_idx].unit);
        free(lasm_records[free_idx].value);
        free(lasm_records[free_idx].desc);
    }
}


void display_records(struct LhpMetadata *lasm_records)
{
    for (size_t idx = 0; idx < rec_idx; idx++) {
        // display record
        printf("#----------------------------------------#\n");
        printf("Record: [%zu]\n", idx);
        printf("#----------------------------------------#\n");
        printf("Mnemonic: [%s]\n", lasm_records[idx].mnemonic_name);
        printf("Unit: [%s]\n", lasm_records[idx].unit);
        printf("Value: [%s]\n", lasm_records[idx].value);
        printf("Description: [%s]\n", lasm_records[idx].desc);
    }
}

