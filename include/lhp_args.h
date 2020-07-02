/*
 * File-Name: lhp_args.h
 * File-Desc: header file for argument parsing functions in lh_parse
 * App-Name: lh_parser
 * Project-Name: Las-Header-Parser
 * Copyright: Copyright (c) 2020, DC Slagel
 * License-Identifier: MIT
 */

#ifndef LHP_ARGS_H
#define LHP_ARGS_H

int arg_parse(int argc, char *argv[]);

char *get_filename_arg(void);

void release_arg_memory(void);

#endif /* LHP_ARGS_H */
