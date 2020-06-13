/*
 * File-Name: lhp_parce.c
 * File-Desc: parsing functions in lh_parse
 * App-Name: lh_parser
 * Project-Name: Las-Header-Parser
 * Copyright: Copyright (c) 2020, DC Slagel
 * License-Identifier: MIT
 */

#include <ctype.h> // iscntrl(), isspace()
#include <stdbool.h> // true, false
#include <stdio.h> // FILE, fclose(), fopen(), fprintf(), perror()
#include <stdlib.h> // malloc()
#include <string.h> // strlen(), strncmp(), strncpy(), strdup()


#include "lhp_parse.h"

/*----------------------------------*/
/* module private variables : start */
/*----------------------------------*/
/* use enum to make line_max constant */
enum { line_max = 1024 };
enum { record_max = 6 };

static char *lhp_section_type = NULL;
static char *lhp_field_buffer = NULL;
static char *mnemonic_name = NULL;
static char *unit = NULL;
static char *value = NULL;
static char *desc = NULL;
static size_t line_len = 0;

// Index locations for the start of each field in a line.
// static size_t line_idx = 0;
static size_t line_indexes[4] = { 0, 0, 0, 0 };

struct record_fields {
    char *mnemonic_name;
    char *unit;
    char *value;
    char *desc;
};

static struct record_fields record_array[record_max];
// consider replacing record_array with a record_linked_list
// struct record_list {
//    struct record_fields record;
//    record_list *next;
// };
/*----------------------------------*/
/* module private variables : finis */
/*----------------------------------*/

/*----------------------------------*/
/* module private functions : start */
/*----------------------------------*/
static FILE *open_lhp_file(const char *lhp_filename);
static void clean_up_end_of_line(char *line);
static void parse_section_type(char *line);
static void parse_mnemonic_name(char *line);
static void parse_unit(char *line);
static void parse_value(char *line);
static void parse_desc(char *line);
static void free_records(void);
static void display_record(void);
/*----------------------------------*/
/* module private functions : finis */
/*----------------------------------*/

void read_las_file(const char *lhp_filename)
{
    FILE *fp;
    char line[line_max];
    /* unused variables
    size_t rec_idx = 0;
    char field_id = '\0';
    char *line_iter;
    */

    fp = open_lhp_file(lhp_filename);

    if (fp == NULL) {
        return;
    }

    // TODO: move fgets() to my_io.c and wrap in my_fgets.c
    while (fgets(line, line_max, fp))
    {
        size_t line_idx = 0;

        clean_up_end_of_line(line);

        parse_section_type(line);

        line_len = strlen(line);

        // Canidate content for fields: name, unit, value, desc
        lhp_field_buffer = malloc(line_len);
        if (lhp_field_buffer == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }

        // Skip spaces at the beginning of the string.
        while (isspace(line[line_idx])) {
          line_idx++;
        }

        // ---------------------------------------------------------------------
        // Parse Mnemonic name.
        // ---------------------------------------------------------------------
        parse_mnemonic_name(line);

        // ---------------------------------------------------------------------
        // Parse unit.
        // ---------------------------------------------------------------------
        parse_unit(line);

        // ---------------------------------------------------------------------
        // Parse value.
        // ---------------------------------------------------------------------
        parse_value(line);


        // ---------------------------------------------------------------------
        // Parse description.
        // ---------------------------------------------------------------------
        parse_desc(line);

        // ---------------------------------------------------------------------
        // Display fields
        // ---------------------------------------------------------------------

        printf("#----------------------------------------#\n");
        printf("Record: [%s]\n", line);
        // %zu: size_t
        printf("Record-Size:  [%zu]\n", strlen(line));
        printf("Record-Size:  [%zu]\n", sizeof(line));
        printf("Mnemonic: [%zu]\n", sizeof(mnemonic_name));
        printf("Mnemonic: [%s]\n", mnemonic_name);

        printf("Unit: [%zu]\n", strlen(unit));
        printf("Unit: [%s]\n", unit);
        printf("Value: [%zu]\n", strlen(value));
        printf("Value: [%s]\n", value);
        printf("Desc: [%zu]\n", strlen(desc));
        printf("Desc: [%s]\n", desc);
        printf("#----------------------------------------#\n");

        return;
    }

    if (fclose(fp) == EOF) {
        perror("close");
    }

    display_record();

    free_records();
}

static void parse_section_type(char *line)
{
    size_t line_len = strlen(line);
    // Get the section type
    if (strncmp("~", line, 1) == 0) {
        lhp_section_type = malloc(line_len);

        if (lhp_section_type != NULL) {
            strncpy(lhp_section_type, line, line_len);
            if (lhp_section_type == NULL) {
                perror("strncpy");
                exit(EXIT_FAILURE);
            }
        }
        // printf("Section Type: [%s]\n\n", lhp_section_type);
    }
}

void parse_mnemonic_name(char *line)
{
    size_t my_idx = 0;
    char *my_buf;
    char *tofree;
    size_t line_idx = line_indexes[0];

    tofree = my_buf = strdup(line);

    while (line[line_idx] != '.') {
      my_buf[my_idx] = line[line_idx];
      line_idx++;
      my_idx++;
    }

    // Move line_idx past the '.' delimiter.
    line_idx++;
    line_indexes[1] = line_idx;

    // Copy buffer to mnemonic_name property
    my_buf[my_idx] = '\0';
    mnemonic_name = strdup(my_buf);

    free(tofree);
}

void parse_unit(char *line)
{
    size_t my_idx = 0;
    char *my_buf;
    char *tofree;

    if (line_indexes[1] == 0) {
      parse_mnemonic_name(line);
    }

    size_t line_idx = line_indexes[1];

    tofree = my_buf = strdup(line + line_idx);

    while (isspace(line[line_idx]) == false) {
      my_buf[my_idx] = line[line_idx];
      line_idx++;
      my_idx++;
    }

    // Move line_idx past the '.' delimiter.
    line_idx++;
    line_indexes[2] = line_idx;

    // Copy buffer to mnemonic_name property
    my_buf[my_idx] = '\0';
    unit = strdup(my_buf);

    free(tofree);
}


void parse_value(char *line)
{
    size_t my_idx = 0;
    char *my_buf;
    char *tofree;

    if (line_indexes[2] == 0) {
      parse_unit(line);
    }

    size_t line_idx = line_indexes[2];

    tofree = my_buf = strdup(line + line_idx);

    while (isspace(line[line_idx]) == true) {
      line_idx++;
    }

    while (line[line_idx] != ':') {
      my_buf[my_idx] = line[line_idx];
      line_idx++;
      my_idx++;
    }

    // Move line_idx past the '.' delimiter.
    line_idx++;
    line_indexes[3] = line_idx;

    // Copy buffer to mnemonic_name property
    my_buf[my_idx] = '\0';
    value = strdup(my_buf);

    free(tofree);
}

void parse_desc(char *line)
{
    size_t my_idx = 0;
    char *my_buf;
    char *tofree;

    if (line_indexes[3] == 0) {
      parse_value(line);
    }

    size_t line_idx = line_indexes[3];

    tofree = my_buf = strdup(line + line_idx);

    while (isspace(line[line_idx]) == true) {
      line_idx++;
    }

    while (line[line_idx] != '\0') {
      my_buf[my_idx] = line[line_idx];
      line_idx++;
      my_idx++;
    }

    // Copy buffer to mnemonic_name property
    my_buf[my_idx] = '\0';
    desc = strdup(my_buf);

    free(tofree);
}



FILE *open_lhp_file(const char *lhp_filename)
{
    FILE *result;
    result = fopen(lhp_filename, "r");

    if (result == NULL)
    {
        fprintf(
            stdout,
            "INFO: config file [%s] not found. Using default settings.\n",
            lhp_filename);
        /* perror("fopen"); */
    }
    return result;
}


static void clean_up_end_of_line(char *line)
{
    // Remove spaces and new-lines from the end of the line
    size_t line_len = strlen(line);
    for (size_t idx = line_len ; idx >= 1; idx--) {
        if (iscntrl(line[idx]) || isspace(line[idx])) {
            line[idx] = '\0';
        }
        else {
            break;
        }
    }
}


void free_records(void)
{
    for (size_t free_idx = 0; free_idx < record_max; free_idx++) {
        // printf("releasing memory for rec_idx [%ld]\n", free_idx);
        free(record_array[free_idx].mnemonic_name);
        free(record_array[free_idx].unit);
        free(record_array[free_idx].value);
        free(record_array[free_idx].desc);
    }
}


void display_record(void)
{
    for (size_t idx = 0; idx < record_max; idx++) {
        // display record
        printf("#----------------------------------------#\n");
        printf("Record: [%zu]\n", idx);
        printf("#----------------------------------------#\n");
        printf("Mnemonic: [%s]\n", record_array[idx].mnemonic_name);
        printf("Unit: [%s]\n", record_array[idx].unit);
        printf("Value: [%s]\n", record_array[idx].value);
        printf("Description: [%s]\n", record_array[idx].desc);
    }
}


