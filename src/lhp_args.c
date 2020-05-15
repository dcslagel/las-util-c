/*
 * File-Name: lhp_args.c
 * File-Desc: argument parsing functions for lh_parse
 * App-Name: lh_parser
 * Project-Name: Las-Header-Parser
 * Copyright: Copyright (c) 2020, DC Slagel
 * License-Identifier: MIT
 */

#include <stdio.h>   // perror()
#include <stdlib.h>  // malloc(), free()
#include <strings.h> // strlen(), strncpy()
#include <getopt.h>  // getopt(), optarg

#include "lhp_args.h"

static char *filename_to_parse = NULL;


int arg_parse(int argc, char *argv[])
{
    int ch;
    char *optstring = "f:";
    
    while ((ch = getopt(argc, argv, optstring)) !=  -1)
    {
        switch (ch) 
        {
            case 'f':
                filename_to_parse = malloc(strlen(optarg + 1));
                if (filename_to_parse == NULL)
                {
                    perror("malloc");
                    return 1;
                }
                // This seems to work but not sure why.
                // strncpy(filename_to_parse, optarg, strlen(optarg) + 1);
                
                // This seems to be the standard way
                strncpy(filename_to_parse, optarg, strlen(optarg));
                filename_to_parse[strlen(filename_to_parse) - 1] = '\0';
                break;
        }
    }

    return 0;
}

char *get_filename_arg(void)
{
    return filename_to_parse;
}

void release_arg_memory(void)
{
    free(filename_to_parse);
}

