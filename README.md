
NAME
----
Las-Header-Parser - A Log Ascii Standard 3.0 header meta-data parser in C

SYNOPSIS
--------

`lh_parse -f` <sample.las>

DESCRIPTION
-----------
Caution: This is Alpha software!

The current goals of `lh_parse` are:
- Parse LAS 3.0 file header meta-data lines.
- Explore the LAS 3.0 file format specification.
- Explore parsing design issues related to C-Lang.

OPTIONS
-------

`-f`
  [a file of LAS header lines to parse]

COMPILE AND RUN
---------------

```bash
cd las-header-parser/src
make clean
make
make install
bin/lh_parser -f examples/3.0/ver_line_30.las
```

This will output:

```
bin/lh_parser -f examples/3.0/ver_line_30.las
filename: [examples/3.0/ver_line_30.las]
#----------------------------------------#
Record: [VERS.                          3.0 : CWLS LOG ASCII STANDARD -VERSION 3.0]
Record-Size:  [73]
Record-Size:  [1024]
Mnemonic: [8]
Mnemonic: [VERS]
Unit: [0]
Unit: []
Value: [4]
Value: [3.0 ]
Desc: [36]
Desc: [CWLS LOG ASCII STANDARD -VERSION 3.0]
#----------------------------------------#
```
PROJECT
-------
The current work-in-progress milestone is 0.0.2:

https://github.com/dcslagel/las-util-django/milestone/4
- Goals:
  - Organize and stabilize the directory structure and makefile(s).
  - Implement basic tests and basic test-suite infrastructure.

las-parser-c's project road-map is managed in github milestones at:

https://github.com/dcslagel/las-header-parser-c/milestones

To request a feature or report a bug create an issue at:

https://github.com/dcslagel/las-header-parser-c/issues

BUGS
----

- Functionality is severely limited to reading the fields from a LAS file
  containing only one meta data line.  Additional functionality will be added
  in future iterations.

- Report bugs by creating an issue at:
  - https://github.com/dcslagel/las-util-django/issues

COPYRIGHT
------

Copyright (c) 2020 DC Slagel and contributors
