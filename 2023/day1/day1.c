#include <ctype.h>
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

char getDigitSpelledOut(char *buffer) {
    if (strstr(buffer, "one")) {
        return '1';
    } else if (strstr(buffer, "two")) {
        return '2';
    } else if (strstr(buffer, "three")) {
        return '3';
    } else if (strstr(buffer, "four")) {
        return '4';
    } else if (strstr(buffer, "five")) {
        return '5';
    } else if (strstr(buffer, "six")) {
        return '6';
    } else if (strstr(buffer, "seven")) {
        return '7';
    } else if (strstr(buffer, "eight")) {
        return '8';
    } else if (strstr(buffer, "nine")) {
        return '9';
    } else {
        return '\0';
    }
}

int part2() {
    long fileLen;
    char *buffer = readFile("day1/test.txt", &fileLen);

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

    char temp[30];
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
            char maybeDigit = getDigitSpelledOut(temp);
            if (maybeDigit != '\0') {
                if (values[0] != '\0') {
                    values[1] = maybeDigit;
                } else {
                    values[0] = maybeDigit;
                }
                // We probably shouldn't be clearing the whole thing, need to handle twone
                // Clear the temp buffer
                memset(temp, 0, sizeof(temp));
                len = 0;
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