#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../config.h"
#include "reader.h"

static int reader_read(void *s, FILE *stream)
{
    reader_t *self = s;

    while (self->num_strings < MAX_STRINGS)
    {
        char *string = calloc(1, sizeof(char));
        if (string == NULL)
        {
            return EXIT_FAILURE_MALLOC_FAILURE;
        }
        int current_char;
        int i = 0;
        while ((current_char = getc(stream)) != '\n')
        {
            if (i == MAX_LENGTH)
            {
                free(string);
                return EXIT_FAILURE_MAX_LEN_REACHED;
            }

            string[i] = current_char;
            char *string_tmp = realloc(string, i + 2);
            i++;
            if (string_tmp == NULL)
            {
                free(string);
                return EXIT_FAILURE_REALLOC_FAILURE;
            }
            string = string_tmp;
            string[i] = '\0';
        }

        printf("Entered string: %s\n", string);

        if (strcmp(string, "exit") == 0)
        {
            free(string);
            break;
        }

        self->strings[self->num_strings] = string;
        self->num_strings++;
    }
    return EXIT_SUCCESS;
}

static void reader_print(void *s)
{
    reader_t *self = s;

    if (self->num_strings == MAX_STRINGS)
    {
        printf("Maximum number of strings reached (%d)\n", MAX_STRINGS);
    }

    puts("\nEntered valid strings:");
    for (int i = 0; i < self->num_strings; i++)
    {
        printf("%s\n", self->strings[i]);
    }
}

static void reader_free(void *s)
{
    reader_t *self = s;

    for (int i = 0; i < self->num_strings; i++)
    {
        free(self->strings[i]);
    }
    free(self->strings);
    free(self);
}

static void reader_initialize(void *s)
{
    reader_t *self = s;
    self->read = &reader_read;
    self->free = &reader_free;
    self->print = &reader_print;
    self->strings = malloc(MAX_STRINGS * sizeof(char *));
    self->num_strings = 0;
}

reader_t *reader_new(void)
{
    reader_t *self = malloc(sizeof(reader_t));
    reader_initialize(self);
    return self;
}