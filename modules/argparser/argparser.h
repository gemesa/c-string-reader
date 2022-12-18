#ifndef C_STRING_READER_ARGPARSER_H
#define C_STRING_READER_ARGPARSER_H

#include <stdio.h>

typedef struct
{
    void (*parse)(void *self, int argc, char **argv);
    void (*free)(void *self);
    void (*print)(void *self);
    FILE *input;
    char *filename;
    int status;
} argparser_t;

extern argparser_t *argparser_new(void);

#endif//C_STRING_READER_ARGPARSER_H
