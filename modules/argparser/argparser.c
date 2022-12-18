#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../config.h"
#include "argparser.h"

void argparser_parse(void *s, int argc, char **argv)
{
    argparser_t *self = s;
    int c;
    char *ptr;
    while ((c = getopt(argc, argv, "ht:")) != -1)
    {
        switch (c)
        {
            case 'h':
                self->status = EXIT_FAILURE;
                break;
            case 't':
                self->input = NULL;
                self->filename = optarg;
                break;
            default:
                self->status = EXIT_FAILURE;
                break;
        }
    }
}

void argparser_print(void *s)
{
    argparser_t *self = s;
    (void) self;

    printf("Usage: c-string-reader [-h] [-t input_file]\n"
           "  -h: print this help message\n"
           "  -t: test mode\n"
           "    - if not specified input is read from stdin\n"
           "    - if specified input is read from an input text file (containing newline separated strings)\n"
           "\n"
           "This program reads some variable length strings from stdin and stores them in an array of pointers to strings.\n"
           "The characters are read one by one until a newline is found (newline will be stripped from the string).\n"
           "After collecting all of them, the strings are printed to stdout.\n"
           "The maximum number of strings is %d and the maximum length of each string is %d. Empty strings are accepted.\n"
           "The program exits if any of the following conditions is true:\n"
           "  - the maximum number of strings is reached,\n"
           "  - \"exit\" string is provided,\n"
           "  - invalid input is provided.\n",
           MAX_STRINGS, MAX_LENGTH);
}

static void argparser_initialize(void *s)
{
    argparser_t *self = s;
    self->parse = &argparser_parse;
    self->free = &free;
    self->print = &argparser_print;
    self->input = stdin;
    self->status = EXIT_SUCCESS;
}

argparser_t *argparser_new(void)
{
    argparser_t *self = malloc(sizeof(argparser_t));
    argparser_initialize(self);
    return self;
}