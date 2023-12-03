#include "read.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *readFile(const char *filename, long *fileLen) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    *fileLen = ftell(file);
    rewind(file);

    char *buffer = malloc(*fileLen + 1);
    if (!buffer) {
        perror("Memory error");
        fclose(file);
        return NULL;
    }

    fread(buffer, *fileLen, 1, file);
    fclose(file);

    buffer[*fileLen] = '\0';

    return buffer;
}
