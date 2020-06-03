
NAME
----
Las-Header-Parser - A Log Ascii Standard 3.0 header meta-data parser in C

SYNOPSIS
--------

`lh_parse -f` <sample.las>

DESCRIPTION
-----------
Caution: This is Alpha software!

The current goal of 'lh_parse` is to parse LAS 3.0 file header meta-data lines.

OPTIONS
-------

`-f`
  a file of las header lines to parse

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

las-parser-c's project road-map is managed in github milestones at:
- https://github.com/dcslagel/las-header-parser-c/milestones

To request a feature or report a bug create an issue at:
- https://github.com/dcslagel/las-header-parser-c/issues

BUGS
----

- Functionality is severly limited to reading the fields from a las file
  containing only one meta data line.  Additional functionality will be added
  in future iterations.

- Report bugs by creating an issue at:
  - https://github.com/dcslagel/las-util-django/issues

COPYRIGHT
------

Copyright (c) 2020 DC Slagel and contributers
