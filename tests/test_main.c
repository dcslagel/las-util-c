/*
 * File-Name: test_main.c
 * File-Desc: Test file for lh_parser
 * App-Name: las-header-parser
 * Project-Name: Las-Header-Parser
 * Copyright: Copyright (c) 2020, DC Slagel
 * License-Identifier: MIT
 */

#include <stdio.h>  // printf
#include <stdlib.h> // exit, EXIT_SUCCESS

#include "lhp_parse.c"

int test_lhp_section_type_is_null(void);
int test_section_type_is_ver(void);
int test_section_type_is_empty(void);

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


int main(void)
{
  int passed = 0;
  int failed = 0;

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

  printf("Total: [%d], Passed: [%d], Failed: [%d]\n",
    passed + failed, passed, failed
  );

  exit(EXIT_SUCCESS);
}
