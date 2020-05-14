
NAME
----
Las-Header-Parser - A Log Ascii Standard header meta-data parser in C

SYNOPSIS
--------

`lh_parse -f` <sample.las>

DESCRIPTION
-----------
Caution: This is very Alpha software!

The goal of 'lh_parse` is to parse LAS file header meta-data lines.

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
./lh_parse -f example-01.las
```

BUGS
----

- Functionality is non-existent. It will be added in future iterations.


COPYRIGHT
------

Copyright (c) 2020 DC Slagel and contributers
