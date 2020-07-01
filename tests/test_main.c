/* 
 * File-Name: test_main.c
 * File-Desc: Test file for lh_parser
 * App-Name: las-header-parser
 * Project-Name: Las-Header-Parser
 * Copyright: Copyright (c) 2020, DC Slagel
 * License-Identifier: MIT
 */

#include <stdio.h>  // printf()
#include <stdlib.h> // exit, EXIT_SUCCESS

#include "lhp_test_parse.h"


int main(void)
{
  int passed = 0;
  int failed = 0;

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
