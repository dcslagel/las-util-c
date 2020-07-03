/* 
 * File-Name: lhp_test_parser.c
 * File-Desc: Test parser functions for lh_parser
 * App-Name: las-header-parser
 * Project-Name: Las-Header-Parser
 * Copyright: Copyright (c) 2020, DC Slagel
 * License-Identifier: MIT
 */

#include <stdio.h>  // printf
#include <stdlib.h> // calloc, exit, EXIT_SUCCESS
#include <string.h> // strcmp()

#include "lhp.h"
#include "lhp_test_parse.h"

static char *test_rec_001 = "VERS.  3.0 : CWLS LOG ASCII STANDARD -VERSION 3.0";
static char *test_rec_002 = "STRT .M      1670.0000              : First Index Value";
static char *test_rec_003 = "STRT .M      1670.0000              : ";


// Configure a record for testing
struct LhpMetadata lasm_record;

// Configure line object
// Add the actual line in the specific test case
struct LhpLine lhpline;


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

