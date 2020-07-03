
NAME
----
Las-Header-Parser - A Log Ascii Standard 3.0 header meta-data parser in C

TABLE-OF-CONTENTS
-----------------
- [DESCRIPTION](#description)
- [SYNOPSIS](#synopsis)
- [OPTIONS](#options)
- [COMPILE-AND-RUN](#compile-and-run)
- [PROJECT-ROADMAP](#project-roadmap)
- [FEATURE-REQUEST](#feature-request)
- [BUGS](#bugs)
- [COPYRIGHT](#copyright)


[DESCRIPTION](#name)
-----------
Caution: This is Alpha software! 

The current goals of `lh_parse` are:
- Parse LAS 3.0 file header meta-data lines.
- Explore the LAS 3.0 file format specification.
- Explore parsing design issues related to C-Lang.

LAS file format versions are written and maintained by
the Canadian Well Logging Society at
https://www.cwls.org/products/


[SYNOPSIS](#name)
--------

`lh_parse -f` <sample.las>

[OPTIONS](#name)
-------

`-f`
  <a file of LAS header lines to parse>


[COMPILE-AND-RUN](#name)
---------------

Las-Header-Parser has been tested with gcc-9 and clang on darwin-amd64.


```bash
cd las-header-parser/src
make clean
make
make install
bin/lh_parser -f examples/3.0/dev_example_30.las
```

This will output:

```
filename: [examples/3.0/dev_example_30.las]
FILESIZE: [399]
#----------------------------------------#
Record: [0]
#----------------------------------------#
Mnemonic: [VERS]
Unit: []
Value: [                         3.0 ]
Description: [ CWLS LOG ASCII STANDARD -VERSION 3.0]
#----------------------------------------#
Record: [1]
#----------------------------------------#
Mnemonic: [WRAP]
Unit: []
Value: [                          NO ]
Description: [ ONE LINE PER DEPTH STEP]
#----------------------------------------#
Record: [2]
#----------------------------------------#
Mnemonic: [DLM ]
Unit: []
Value: [                       COMMA ]
Description: [ DELIMITING CHARACTER BETWEEN DATA COLUMNS]
#----------------------------------------#
Record: [3]
#----------------------------------------#
Mnemonic: [STRT ]
Unit: [M]
Value: [             1670.0000                ]
Description: [ First Index Value]
```

[PROJECT-ROADMAP](#name)
------------
The current work-in-progress milestone is 0.0.4:

https://github.com/dcslagel/las-header-parser-c/milestone/6
- Goals:
  - Inital iteration of parsing related Parameter and Data sections

las-parser-c's project road-map is managed in github milestones at:

https://github.com/dcslagel/las-header-parser-c/milestones

To request a feature or report a bug create an issue at:

https://github.com/dcslagel/las-header-parser-c/issues


[FEATURE-REQUEST](#name)
----------------

To request and discuss a potiential feature create an issue at:
  - https://github.com/dcslagel/las-header-parser-c/issues


[BUGS](#name)
----

- Functionality is limited to reading the fields from a LAS file containing
  only the v2.0 type sections.  Additional functionality will be added in
  future iterations.

- Report bugs by creating an issue at:
  - https://github.com/dcslagel/las-header-parser-c/issues

[COPYRIGHT](#name)
------

Copyright (c) 2020 DC Slagel and contributors
