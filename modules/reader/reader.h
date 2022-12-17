#ifndef C_STRING_READER_READER_H
#define C_STRING_READER_READER_H

#include <stdio.h>

enum
{
    EXIT_FAILURE_MAX_LEN_REACHED = 2,
    EXIT_FAILURE_MALLOC_FAILURE = 3,
    EXIT_FAILURE_REALLOC_FAILURE = 4
};

typedef struct
{
    int (*read)(void *self, FILE *stream);
    void (*free)(void *self);
    void (*print)(void *self);
    char **strings;
    int num_strings;
} reader_t;

extern reader_t *reader_new(void);

#endif//C_STRING_READER_READER_H
