/*
 * File-Name: main.c
 * File-Desc: Main file for lh_parser
 * App-Name: las-header-parser
 * Project-Name: Las-Header-Parser
 * Copyright: Copyright (c) 2020, DC Slagel
 * License-Identifier: MIT
 */

#include <stdio.h>  // printf
#include <stdlib.h> // exit, EXIT_SUCCESS

#include "lhp.h"

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("usage: %s -f <filename>\n", argv[0]);
        exit(EXIT_SUCCESS);
    }

    if (arg_parse(argc, argv) != 0) {
        exit(1);
    }

    char *file_to_parse = get_filename_arg();
    printf("filename: [%s]\n", file_to_parse);

    parse_las_file(file_to_parse);
    
    release_arg_memory();

    exit(EXIT_SUCCESS);
}
