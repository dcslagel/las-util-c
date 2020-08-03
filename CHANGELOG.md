# CHANGELOG

## 0.0.3 - 2020-07-03

Refactor the basic parsing functions and data structures to remove duplication and improve maintainability

### Added

#### Add LAS file with well section

- Add LAS file with well section
- Add dynamic allocation of the record array
- Add estimate array size from filesize
- Adopt test cases for the record array

#### Initial Section structs and functionality

- Standardize header defines on LHP_ prefix
- Add basic section tests
- Add Section header and c file for sections structs

### Changed

#### Store parsed fields in an array of struct

- Move parsed metadata fields to an array of structs
- Rename makefile and ver_line_30.las
- Enable parsing Section headers and comments


#### Refactor main parser

- Move file functions to lhp_file.c
- Change lhp_parse to use lhp_file
- Move initial line services to lhp_line.c
- Move line iteration config to lhp_line.c
- Move metadata services to lhp_metadata.c
- Change parse_.. funcs parameters
- Move detail parse functions to lhp_metadata.c
- Refactor LAS field parsing
- Update test file to handle the refactored parsing


#### Separate test definitions from test engine

## 0.0.2 - 2020-06-15

### Added

- Organize and stabilize the directory structure and makefile(s).
- Implement basic tests and basic test-suite infrastructure.


## 0.0.1 - 2020-05-18

Initial tag

### Added

- Initial README.md and LICENCE.md files
- Alpha-level code for parsing one line
