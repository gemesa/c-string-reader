#include <stdio.h>
#include <stdlib.h>

#include "modules/reader/reader.h"

int main(void)
{
    char *filename = "test/input.txt";
    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        perror(filename);
        return EXIT_FAILURE;
    }

    reader_t *reader = reader_new();

    puts("Enter strings:");
    switch (reader->read(reader, file))
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
    (void) fclose(file);
    reader->free(reader);

    return EXIT_SUCCESS;
}
