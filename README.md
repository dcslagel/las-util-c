
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
./lh_parse -f header_line.las
```

This will output:

```
$ ./lh_parser -f header_line.las
filename: [header_line.las]
#----------------------------------------#
Record: [ BHT .DEGC         35.5000:   BOTTOM HOLE TEMPERATURE]
Record-Size:  [53]
Mnemonic: [BHT ]
#----------------------------------------#
```

BUGS
----

- Functionality is severly limited to reading the mnemonic_name (first field)
  from a las file containing only one meta data line.  Additional functionality
  will be added in future iterations.


COPYRIGHT
------

Copyright (c) 2020 DC Slagel and contributers
