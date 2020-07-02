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

#include "lhp.h"

//-------------------------------------------------------------------
// module private variables : start
//-------------------------------------------------------------------
static size_t rec_idx = 0;
//-------------------------------------------------------------------
// module private variables : finis
//-------------------------------------------------------------------

//-------------------------------------------------------------------
// module private functions : start
//-------------------------------------------------------------------
static void free_records(struct LhpMetadata* lasm_records, size_t lhp_array_size);
static void display_records(struct LhpMetadata* lasm_records);
//-------------------------------------------------------------------
// module private functions : finis
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// API: public-functions
//-------------------------------------------------------------------
void parse_las_file(const char *lhp_filename)
{
    struct LhpFile lhpfile;
    lhp_file_init(&lhpfile, lhp_filename);

    struct LhpLine lhpline;
    lhp_line_init(&lhpline);

    struct LhpData lhpdata;
    lhp_data_init(&lhpdata, lhpfile.size);

    struct LhpSections lhpsections;
    lhp_sections_init(&lhpsections);

    // Memory: free(lasm_records); when done.
    struct LhpMetadata *lasm_records = lhpdata.array;

    while (fgets(lhpline.line, lhpline.size, lhpfile.fp))
    {
        lhp_line_config(&lhpline);
        if (lhp_section_parse(&lhpsections, lhpline.line, rec_idx)) {
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
    // display_sections(&lhpsections);

    free_records(lasm_records, lhpdata.len);
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

