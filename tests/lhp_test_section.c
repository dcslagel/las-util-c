/* 
 * File-Name: lhp_test_section.c
 * File-Desc: Test section functions for lh_parser
 * App-Name: las-header-parser
 * Project-Name: Las-Header-Parser
 * Copyright: Copyright (c) 2020, DC Slagel
 * License-Identifier: MIT
 */

#include <string.h> // strcmp()

#include "lhp_section.h"
#include "lhp_test_section.h"


// Configure a record for testing
struct LhpSections lhpsections;


int test_is_section(void) {
  lhp_sections_init(&lhpsections);
  char* line = "~VERSION";
  size_t rec_idx = 0;
  if (lhp_section_parse(&lhpsections, line, rec_idx)) {
    return(1);
  } else {
    return(0);
  }

}

int test_is_not_section(void) {
  lhp_sections_init(&lhpsections);
  char* line = "STRT .M      1670.0000              : First Index Value";
  size_t rec_idx = 0;
  if (lhp_section_parse(&lhpsections, line, rec_idx)) {
    return(0);
  } else {
    return(1);
  }
}

int test_sections(void) {
  /*
   * #----------------------------------------#
   * Section Record: [0]
   * #----------------------------------------#
   * Mnemonic: [~VERSION]
   * Start_idx: [0]
   * Finis_idx: [1]
   * #----------------------------------------#
   * Section Record: [1]
   * #----------------------------------------#
   * Mnemonic: [~Well Information]
   * Start_idx: [2]
   * Finis_idx: [2]
   *
   */
  lhp_sections_init(&lhpsections);

  // init to 1 (pass), we will change to 0 if any test fails
  int result = 1; 

  // Init/Mock
  char* line = "~VERSION";
  size_t rec_idx = 0;
  lhp_section_parse(&lhpsections, line, rec_idx);

  line = "VERS.                          3.0 : CWLS LOG ASCII STANDARD -VERSION 3.0";
  lhp_section_parse(&lhpsections, line, rec_idx);
  rec_idx++;

  line = "WRAP.                           NO : ONE LINE PER DEPTH STEP";
  lhp_section_parse(&lhpsections, line, rec_idx);
  rec_idx++;

  line = "~Well Information";
  lhp_section_parse(&lhpsections, line, rec_idx);
  rec_idx++;

  line = "STRT .M              1670.0000                : First Index Value";
  lhp_section_parse(&lhpsections, line, rec_idx);
  rec_idx++;

  // Tests
  if (lhpsections.array[0].start_idx != 0) {
    result = 0;
  }
  if (lhpsections.array[0].finis_idx != 1) {
    result = 0;
  }
  if (lhpsections.idx != 1) {
    result = 0;
  }
  if (lhpsections.array[1].finis_idx != 2) {
    result = 0;
  }

  return(result);
  
}
