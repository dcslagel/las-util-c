/* * File-Name: test_main.c * File-Desc: Test file for lh_parser
 * App-Name: las-header-parser
 * Project-Name: Las-Header-Parser
 * Copyright: Copyright (c) 2020, DC Slagel
 * License-Identifier: MIT
 */

#include <stdio.h>  // printf
#include <stdlib.h> // calloc, exit, EXIT_SUCCESS

#include "lhp_file.c"
#include "lhp_line.c"
#include "lhp_metadata.c"
#include "lhp_parse.c"


int test_parse_mnemonic(void); 
int test_lhp_section_type_is_null(void);
int test_section_type_is_ver(void);
int test_section_type_is_empty(void);

static char *test_rec_001 = "VERS.  3.0 : CWLS LOG ASCII STANDARD -VERSION 3.0";
static char *test_rec_002 = "STRT .M      1670.0000              : First Index Value";
static char *test_rec_003 = "STRT .M      1670.0000              : ";

// Configure a record for testing
struct LhpMetadata lasm_record;

// Configure line object
// Add the actual line in the specific test case
struct LhpLine lhpline;

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
  lhp_line_init(&lhpline);
  lhpline.line = test_rec_001;
  parse_data_line(&lasm_record, &lhpline);
  char* want = "VERS";
  if (strcmp(lasm_record.mnemonic_name, want) == 0) {
    return(1);
  } else {
    printf(
        "FAILED: test_parse_mnemonic_name:\n\tactual: [%s]\n\twant: [%s]\n",
        lasm_record.unit, want);
    return(0);
  }
  return(1);
}

int test_parse_empty_unit(void) {
  lhp_line_init(&lhpline);
  lhpline.line = test_rec_001;
  parse_data_line(&lasm_record, &lhpline);
  char* want = "";
  if (strcmp(lasm_record.unit, want) == 0) {
    return(1);
  } else {
    printf(
        "FAILED: test_parse_unit:\n\tactual: [%s]\n\twant: [%s]\n",
        lasm_record.unit, want);
    return(0);
  }
  return(1);
}

int test_parse_m_unit(void) {
  lhp_line_init(&lhpline);
  lhpline.line = test_rec_002;
  parse_data_line(&lasm_record, &lhpline);
  char* want = "M";
  if (strcmp(lasm_record.unit, want) == 0) {
    return(1);
  } else {
    printf(
        "FAILED: test_parse_unit:\n\tactual: [%s]\n\twant: [%s]\n",
        lasm_record.unit, want);
    return(0);
  }
  return(1);
}

int test_parse_value(void) {
  lhp_line_init(&lhpline);
  lhpline.line = test_rec_001;
  parse_data_line(&lasm_record, &lhpline);
  char* want = " 3.0 ";
  if (strcmp(lasm_record.value, want) == 0) {
    return(1);
  } else {
    printf(
        "FAILED: test_parse_value:\n\tactual: [%s]\n\twant: [%s]\n",
        lasm_record.value, want);
    return(0);
  }
  return(1);
}

int test_parse_desc(void) {
  lhp_line_init(&lhpline);
  lhpline.line = test_rec_001;
  parse_data_line(&lasm_record, &lhpline);
  char* want = " CWLS LOG ASCII STANDARD -VERSION 3.0";
  if (strcmp(lasm_record.desc, want) == 0) {
    return(1);
  } else {
    printf(
        "FAILED: test_parse_desc:\n\tactual: [%s]\n\twant: [%s]\n",
        lasm_record.desc, want);
    return(0);
  }
  return(1);
}

int test_parse_empty_desc(void) {
  lhp_line_init(&lhpline);
  lhpline.line = test_rec_003;
  parse_data_line(&lasm_record, &lhpline);
  char* want = " ";
  if (strcmp(lasm_record.desc, want) == 0) {
    return(1);
  } else {
    printf(
        "FAILED: test_parse_desc:\n\tactual: [%s]\n\twant: [%s]\n",
        lasm_record.desc, want);
    return(0);
  }
  return(1);
}

int main(void)
{
  int passed = 0;
  int failed = 0;

  /*
  struct lasm_record *lasm_records = calloc(test_file_size, sizeof(struct lasm_record));
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

  if (test_parse_m_unit()) {
    passed = passed + 1;
  } else {
    failed = failed + 1;
  }

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
