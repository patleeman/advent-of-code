#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../utils/read.h"

int part1() {
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

typedef enum {
    SEARCH_FROM_START,
    SEARCH_FROM_END
} SearchDirection;

char getDigitSpelledOut(const char *buffer, SearchDirection direction) {
    const char *found = NULL;

    if (direction == SEARCH_FROM_START) {
        // Search from the start of the buffer
        if ((found = strstr(buffer, "one")))
            return '1';
        else if ((found = strstr(buffer, "two")))
            return '2';
        else if ((found = strstr(buffer, "three")))
            return '3';
        else if ((found = strstr(buffer, "four")))
            return '4';
        else if ((found = strstr(buffer, "five")))
            return '5';
        else if ((found = strstr(buffer, "six")))
            return '6';
        else if ((found = strstr(buffer, "seven")))
            return '7';
        else if ((found = strstr(buffer, "eight")))
            return '8';
        else if ((found = strstr(buffer, "nine")))
            return '9';
    } else {
        // Search from the end of the buffer
        size_t len = strlen(buffer);
        for (size_t i = len; i > 0; --i) {
            const char *subBuffer = &buffer[i - 1];
            if (strncmp(subBuffer, "one", 3) == 0)
                return '1';
            else if (strncmp(subBuffer, "two", 3) == 0)
                return '2';
            else if (strncmp(subBuffer, "three", 5) == 0)
                return '3';
            else if (strncmp(subBuffer, "four", 4) == 0)
                return '4';
            else if (strncmp(subBuffer, "five", 4) == 0)
                return '5';
            else if (strncmp(subBuffer, "six", 3) == 0)
                return '6';
            else if (strncmp(subBuffer, "seven", 5) == 0)
                return '7';
            else if (strncmp(subBuffer, "eight", 5) == 0)
                return '8';
            else if (strncmp(subBuffer, "nine", 4) == 0)
                return '9';
        }
    }

    return '\0';  // No match found
}
int part2() {
    long fileLen;
    char *buffer = readFile("day1/data.txt", &fileLen);

    if (!buffer) {
        perror("Error reading file");
        return 1;
    }

    int sum = 0;

    char values[3];
    values[0] = '\0';
    values[1] = '\0';
    values[2] = '\0';

    int lineCount = 0;
    int i = 0;

    char temp[100];
    int len = 0;
    do {
        char ch = buffer[i];
        if (ch != '\n') {
            printf("%c", ch);
        }
        if (ch == '\n' || ch == '\0') {
            lineCount++;

            // Handle case where there is only one number. It's first and last.
            if (values[1] == '\0') {
                values[1] = values[0];
            }

            int result = atoi(values);
            printf(" [Result: %d Sum: %d Char1: %c Char2: %c]\n", result, sum, values[0], values[1]);
            sum += result;
            values[0] = '\0';
            values[1] = '\0';

            // Clear the temp buffer
            memset(temp, 0, sizeof(temp));
            len = 0;
        }

        if (isdigit(ch)) {
            if (values[0] != '\0') {
                values[1] = ch;
            } else {
                values[0] = ch;
            }

            // Clear the temp buffer
            memset(temp, 0, sizeof(temp));
            len = 0;
        } else {
            if (len < sizeof(temp) - 1) {
                temp[len] = ch;
                len++;
            } else {
                printf("ERROR: Buffer overflow\n");
            }
            temp[len] = '\0';
            if (values[0] == '\0') {
                char maybeDigit = getDigitSpelledOut(temp, SEARCH_FROM_START);
                if (maybeDigit != '\0') {
                    values[0] = maybeDigit;
                }
            } else {
                char maybeDigit = getDigitSpelledOut(temp, SEARCH_FROM_END);
                if (maybeDigit != '\0') {
                    values[1] = maybeDigit;
                }
            }
        }
    } while (buffer[i++] != '\0');

    printf("Sum: %d\n", sum);
    printf("Lines: %d\n", lineCount);
    free(buffer);
    return 0;
}

int main() {
    // part1();
    return part2();
}