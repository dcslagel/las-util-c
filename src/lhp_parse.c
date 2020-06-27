/*
 * File-Name: lhp_parce.c
 * File-Desc: parsing functions in lh_parse
 * App-Name: lh_parser
 * Project-Name: Las-Header-Parser
 * Copyright: Copyright (c) 2020, DC Slagel
 * License-Identifier: MIT
 */

#include <ctype.h> // iscntrl(), isspace()
#include <errno.h>
#include <stdbool.h> // true, false
#include <stdio.h> // FILE, fclose(), fopen(), fprintf(), perror()
#include <stdlib.h> // malloc()
#include <string.h> // strlen(), strncmp(), strncpy(), strdup()
#include <sys/stat.h>
#include <sys/types.h>


#include "lhp_parse.h"

/*----------------------------------*/
/* module private variables : start */
/*----------------------------------*/
/* use enum to make line_buf_size constant */
enum { line_buf_size = 1024 };

static char *lhp_section_type = NULL;
static char *lhp_field_buffer = NULL;
static size_t rec_idx = 0;
static size_t lhp_array_size = 0;

// Index locations for the start of each field in a line.
// static size_t line_idx = 0;
static size_t line_indexes[4] = { 0, 0, 0, 0 };

// 'lasm' is short for Log Ascii Standard Metadata
struct lasm_record {
    char *mnemonic_name;
    char *unit;
    char *value;
    char *desc;
};
/*----------------------------------*/
/* module private variables : finis */
/*----------------------------------*/

/*----------------------------------*/
/* module private functions : start */
/*----------------------------------*/
static FILE *open_lhp_file(const char *lhp_filename);
static off_t get_file_size(const char *lhp_filename);

static size_t estimate_array_size(const off_t file_size);

static void clean_up_end_of_line(char *line);
static size_t parse_section_type(char *line);

static void parse_mnemonic_name(char *line, struct lasm_record *lasm_records);
static void parse_unit(char *line, struct lasm_record *lasm_records);
static void parse_value(char *line, struct lasm_record *lasm_records);
static void parse_desc(char *line, struct lasm_record *lasm_records);

static void free_records(struct lasm_record *lasm_records);
static void display_records(struct lasm_record *lasm_records);
/*----------------------------------*/
/* module private functions : finis */
/*----------------------------------*/

void read_las_file(const char *lhp_filename)
{
    FILE *fp;
    char line[line_buf_size];
    size_t line_len = 0;
    off_t lhp_filesize = 0;

    lhp_filesize = get_file_size(lhp_filename);
    printf("FILESIZE: [%lld]\n", lhp_filesize);

    lhp_array_size = estimate_array_size(lhp_filesize);
    printf("ARRAY-SIZE: [%zu]\n", lhp_array_size);
    struct lasm_record *lasm_records = calloc(lhp_array_size, sizeof(struct lasm_record));
    if (!lasm_records) {
        fprintf(stderr, "error: virtual memory exhausted: Unable to create lasm_records array.\n");
        exit(EXIT_FAILURE);
    }

    
    fp = open_lhp_file(lhp_filename);

    if (fp == NULL) {
        return;
    }

    while (fgets(line, line_buf_size, fp))
    {
        size_t line_idx = 0;

        clean_up_end_of_line(line);
        if (parse_section_type(line)) {
          continue;
        }


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

        if (strncmp("#", line, 1) == 0) {
          continue;
        }

        // ---------------------------------------------------------------------
        // Parse fields for the current line/record
        // ---------------------------------------------------------------------
        parse_mnemonic_name(line, lasm_records);
        parse_unit(line, lasm_records);
        parse_value(line, lasm_records);
        parse_desc(line, lasm_records);

        rec_idx = rec_idx + 1;

        printf("REC-IDX: %zu, MAX: %zu\n", rec_idx, lhp_array_size);

        // return;
    }

    if (fclose(fp) == EOF) {
        perror("close");
    }

    display_records(lasm_records);

    free_records(lasm_records);
}

static size_t parse_section_type(char *line)
{
    size_t is_section = 0;    
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
        is_section = 1;
        printf("Section Type: [%s]\n\n", lhp_section_type);
    }
    return(is_section);
}

void parse_mnemonic_name(char *line, struct lasm_record *lasm_records)
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
    lasm_records[rec_idx].mnemonic_name = strdup(my_buf);

    free(tofree);
}

void parse_unit(char *line, struct lasm_record *lasm_records)
{
    size_t my_idx = 0;
    char *my_buf;
    char *tofree;

    if (line_indexes[1] == 0) {
      parse_mnemonic_name(line, lasm_records);
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
    lasm_records[rec_idx].unit = strdup(my_buf);

    free(tofree);
}


void parse_value(char *line, struct lasm_record *lasm_records)
{
    size_t my_idx = 0;
    char *my_buf;
    char *tofree;

    if (line_indexes[2] == 0) {
      parse_unit(line, lasm_records);
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
    lasm_records[rec_idx].value = strdup(my_buf);

    free(tofree);
}

void parse_desc(char *line, struct lasm_record *lasm_records)
{
    size_t my_idx = 0;
    char *my_buf;
    char *tofree;

    if (line_indexes[3] == 0) {
      parse_value(line, lasm_records);
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
    lasm_records[rec_idx].desc = strdup(my_buf);

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

off_t get_file_size(const char *filename) {
    struct stat st;

    if (stat(filename, &st) == 0)
        return st.st_size;

    fprintf(stderr, "Cannot determine size of %s: %s\n",
            filename, strerror(errno));

    return -1;
}

size_t estimate_array_size(const off_t file_size) {
  const size_t estimated_average_bytes_per_line = 55;

  if (file_size > 0) {
    return (size_t)file_size / estimated_average_bytes_per_line;
  }
  return 0;
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


void free_records(struct lasm_record *lasm_records)
{
    for (size_t free_idx = 0; free_idx < lhp_array_size; free_idx++) {
        // printf("releasing memory for rec_idx [%ld]\n", free_idx);
        free(lasm_records[free_idx].mnemonic_name);
        free(lasm_records[free_idx].unit);
        free(lasm_records[free_idx].value);
        free(lasm_records[free_idx].desc);
    }
}


void display_records(struct lasm_record *lasm_records)
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

