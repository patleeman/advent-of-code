#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../utils/read.h"

int main() {
    long fileLen;
    char *buffer = readFile("day1/data.txt", &fileLen);

    if (!buffer) {
        perror("Error reading file");
        return 1;
    }

    int lineCount = 0;
    char values[3];
    values[0] = '\0';
    values[1] = '\0';
    values[2] = '\0';
    int sum = 0;
    int i = 0;
    do {
        char ch = buffer[i];
        printf("%c", ch);
        if (ch == '\n' || ch == '\0') {
            lineCount++;

            // Handle case where there is only one number. It's first and last.
            if (values[1] == '\0') {
                values[1] = values[0];
            }

            int result = atoi(values);
            printf("%d / %d (%c/%c)\n", result, sum, values[0], values[1]);
            sum += result;
            values[0] = '\0';
            values[1] = '\0';
        }

        if (isdigit(ch)) {
            if (values[0] != '\0') {
                values[1] = ch;
            } else {
                values[0] = ch;
            }
        }

    } while (buffer[i++] != '\0');

    printf("Sum: %d\n", sum);
    printf("Lines: %d\n", lineCount);
    free(buffer);
    return 0;
}