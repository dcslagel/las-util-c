/*
 * File-Name: test_main.c
 * File-Desc: Test file for lh_parser
 * App-Name: las-header-parser
 * Project-Name: Las-Header-Parser
 * Copyright: Copyright (c) 2020, DC Slagel
 * License-Identifier: MIT
 */

#include <stdio.h>  // printf
#include <stdlib.h> // calloc, exit, EXIT_SUCCESS

#include "lhp_parse.c"

// resets lhp_parser.line_indexes[]
void reset_line_indexes(void);

int test_parse_mnemonic(void); 
int test_lhp_section_type_is_null(void);
int test_section_type_is_ver(void);
int test_section_type_is_empty(void);

static char *test_rec_001 = "VERS.  3.0 : CWLS LOG ASCII STANDARD -VERSION 3.0";
static char *test_rec_002 = "STRT .M      1670.0000              : First Index Value";
static char *test_rec_003 = "STRT .M      1670.0000              : ";

// Configure array of records for testing
static size_t test_array_size = 1;
struct lasm_record *lasm_records = NULL;

// resets lhp_parser.line_indexes[]
void reset_line_indexes(void)
{
  line_indexes[0] = 0;
  line_indexes[1] = 0;
  line_indexes[2] = 0;
  line_indexes[3] = 0;
}

int test_lhp_section_type_is_null(void) {
  if (lhp_section_type == NULL) {
    return(1);
  } else {
    return(0);
  }
}

int test_section_type_is_ver(void) {
  parse_section_type("~VER");
  if (strcmp(lhp_section_type, "~VER") == 0) {
    return(1);
  } else {
    return(0);
  }
}

int test_section_type_is_empty(void) {
  memset(lhp_section_type,0,strlen(lhp_section_type));
  if (strcmp(lhp_section_type, "") == 0) {
    return(1);
  } else {
    return(0);
  }
}

int test_parse_mnemonic(void) {
  struct lasm_record *lasm_records = calloc(test_array_size, sizeof(struct lasm_record));
  parse_mnemonic_name(test_rec_001, lasm_records);
  if (strcmp(lasm_records[0].mnemonic_name, "VERS") == 0) {
    return(1);
  } else {
    printf("FAILED: test_parse_mnemonic_name: actual: [%s]\n", lasm_records[1].mnemonic_name);
    return(0);
  }
  return(1);
}

int test_parse_empty_unit(void) {
  struct lasm_record *lasm_records = calloc(test_array_size, sizeof(struct lasm_record));
  parse_unit(test_rec_001, lasm_records);
  if (strcmp(lasm_records[0].unit, "") == 0) {
    return(1);
  } else {
    printf("FAILED: test_parse_unit: actual: [%s]\n", lasm_records[1].unit);
    return(0);
  }
  return(1);
}

int test_parse_m_unit(void) {
  struct lasm_record *lasm_records = calloc(test_array_size, sizeof(struct lasm_record));
  parse_unit(test_rec_002, lasm_records);
  if (strcmp(lasm_records[0].unit, "M") == 0) {
    return(1);
  } else {
    printf("FAILED: test_parse_unit: actual: [%s]\n", lasm_records[1].unit);
    return(0);
  }
  return(1);
}

int test_parse_value(void) {
  struct lasm_record *lasm_records = calloc(test_array_size, sizeof(struct lasm_record));
  parse_value(test_rec_001, lasm_records);
  if (strcmp(lasm_records[0].value, "3.0 ") == 0) {
    return(1);
  } else {
    printf("FAILED: test_parse_value: actual: [%s]\n", lasm_records[1].value);
    return(0);
  }
  return(1);
}

int test_parse_desc(void) {
  struct lasm_record *lasm_records = calloc(test_array_size, sizeof(struct lasm_record));
  parse_desc(test_rec_001, lasm_records);
  if (strcmp(lasm_records[0].desc, "CWLS LOG ASCII STANDARD -VERSION 3.0") == 0) {
    return(1);
  } else {
    printf("FAILED: test_parse_desc: actual: [%s]\n", lasm_records[1].desc);
    return(0);
  }
  return(1);
}

int test_parse_empty_desc(void) {
  struct lasm_record *lasm_records = calloc(test_array_size, sizeof(struct lasm_record));
  parse_desc(test_rec_003, lasm_records);
  if (strcmp(lasm_records[0].desc, "") == 0) {
    return(1);
  } else {
    printf("FAILED: test_parse_desc: actual: [%s]\n", lasm_records[1].desc);
    return(0);
  }
  return(1);
}

int main(void)
{
  int passed = 0;
  int failed = 0;

  /*
  struct lasm_record *lasm_records = calloc(test_array_size, sizeof(struct lasm_record));
  if (!lasm_records) {
      fprintf(stderr, "error: virtual memory exhausted: Unable to create lasm_records array.\n");
      exit(EXIT_FAILURE);
  }
  */

  if (test_lhp_section_type_is_null()) {
    passed = passed + 1;
  } else {
    failed = failed + 1;
  }

  if (test_section_type_is_ver()) {
    passed = passed + 1;
  } else {
    failed = failed + 1;
  }

  if (test_section_type_is_empty()) {
    passed = passed + 1;
  } else {
    failed = failed + 1;
  }

  // Test a line
  if (test_parse_mnemonic()) {
    passed = passed + 1;
  } else {
    failed = failed + 1;
  }

  if (test_parse_empty_unit()) {
    passed = passed + 1;
  } else {
    failed = failed + 1;
  }

  if (test_parse_value()) {
    passed = passed + 1;
  } else {
    failed = failed + 1;
  }

  if (test_parse_desc()) {
    passed = passed + 1;
  } else {
    failed = failed + 1;
  }

  // Test a different line 
  // So rest line indexes
  reset_line_indexes();

  if (test_parse_m_unit()) {
    passed = passed + 1;
  } else {
    failed = failed + 1;
  }

  // Test a different line 
  // So rest line indexes
  reset_line_indexes();
  if (test_parse_empty_desc()) {
    passed = passed + 1;
  } else {
    failed = failed + 1;
  }

  printf("Total: [%d], Passed: [%d], Failed: [%d]\n",
    passed + failed, passed, failed
  );

  exit(EXIT_SUCCESS);
}
