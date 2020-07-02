/*
 * File-Name: lhp_section.h
 * File-Desc: header file for section services in lh_parse
 * App-Name: lh_parser
 * Project-Name: Las-Header-Parser
 * Copyright: Copyright (c) 2020, DC Slagel
 * License-Identifier: MIT
 */

#ifndef LHP_SECTION_H
#define LHP_SECTION_H

/* public structs : start */
struct LhpSection {
  char *name;
  size_t start_idx;
  size_t finis_idx;
};

struct LhpSections {
  struct LhpSection* array;
  size_t len;
  size_t idx;
};
/* public structs : finis */

/* public-functions */
// extern void lhp_section_init(struct LhpSections* lhpsection);
extern void lhp_sections_init(struct LhpSections*);
extern size_t lhp_section_parse(
    struct LhpSections* lhpsections, char* line, size_t rec_idx);
extern void display_sections(struct LhpSections*);
// extern void lhp_section_config(struct LhpSection* lhpsection);
/* end public-functions */

#endif /* LHP_SECTION_H */
