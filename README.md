
NAME
----
Las-Header-Parser - A Log Ascii Standard header meta-data parser in C

SYNOPSIS
--------

`lhparse -f` *.qif

DESCRIPTION
-----------
Caution: This is very beta software!

The goal of 'lhparse` is to parse LAS file header meta-data lines. 

OPTIONS
-------

`-f`
  a file of las header lines to parse

COMPILE AND RUN
---------------

`cd las-header-line-parser/src`  
`make clean`
`make`  
`./lhparse -f example-01.las`  

BUGS
----

- Functionality is very basic.


COPYRIGHT
------

Copyright (c) 2020 DC Slagel
