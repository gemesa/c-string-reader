#include <stdio.h>
#include <stdlib.h>

#include "modules/argparser/argparser.h"
#include "modules/reader/reader.h"

int main(int argc, char **argv)
{
    argparser_t *argparser = argparser_new();
    argparser->parse(argparser, argc, argv);

    if (argparser->status == EXIT_FAILURE)
    {
        argparser->print(argparser);
        argparser->free(argparser);
        return EXIT_FAILURE;
    }

    if (argparser->input != stdin)
    {
        argparser->input = fopen(argparser->filename, "r");

        if (argparser->input == NULL)
        {
            perror(argparser->filename);
            argparser->free(argparser);
            return EXIT_FAILURE;
        }
    }

    reader_t *reader = reader_new();

    puts("Enter strings:");
    switch (reader->read(reader, argparser->input))
    {
        case EXIT_FAILURE_MAX_LEN_REACHED:
            puts("Invalid input (maximum length reached)");
            break;
        case EXIT_FAILURE_MALLOC_FAILURE:
            puts("malloc failure");
            break;
        case EXIT_FAILURE_REALLOC_FAILURE:
            puts("realloc failure");
            break;
        default:
            break;
    }

    reader->print(reader);
    (void) fclose(argparser->input);
    reader->free(reader);
    argparser->free(argparser);

    return EXIT_SUCCESS;
}
