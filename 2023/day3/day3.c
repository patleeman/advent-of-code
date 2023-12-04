#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../utils/read.c"

int getRowLen(char *data) {
    int row_len = 0;
    while (data[row_len] != '\n') {
        row_len++;
    }
    // Account for the newline
    return row_len + 1;
}

// If a character is not alphanumeric, and not a '.', its a symbol
bool isSymbol(char c) {
    bool isASymbol = !isalnum((unsigned char)c) && c != '.' && c != '\n' && c != '\0' && c != ' ';
    // printf("isSymbol(%c): %d\n", c, isASymbol);
    return isASymbol;
}

bool charAtIndexIsSymbol(int index, char *data, int rowLen) {
    int indicies[8] = {
        // North
        index - rowLen,
        // North East
        index - rowLen + 1,
        // East
        index + 1,
        // South East
        index + rowLen + 1,
        // South
        index + rowLen,
        // South West
        index + rowLen - 1,
        // West
        index - 1,
        // North West
        index - rowLen - 1,
    };

    bool isASymbol = false;

    for (int i = 0; i < 8; i++) {
        // printf("index: %d\n", indicies[i]);
        int idx = indicies[i];
        if (idx < 0 || idx > strlen(data)) {
            continue;
        }
        char c = data[idx];
        if (isSymbol(c)) {
            isASymbol = true;
        }
    }
    return isASymbol;
}

int main() {
    long fileLen;
    char *data = readFile("day3/data.txt", &fileLen);
    int rowLen = getRowLen(data);

    int sum = 0;

    int idx = 0;

    // Temp storage of digits
    char temp[10];
    int tempLen = 0;
    bool tempIsValid = false;

    // Iterate through each character in the file string.
    // If its a newline, increment the row, reset the column.
    while (data[idx] != '\0') {
        printf("idx: %d (%c)", idx, data[idx]);

        if (isdigit((unsigned char)data[idx])) {
            // Store the digit in a temp buffer.
            temp[tempLen++] = data[idx];

            // Check surrounding values to check if valid
            // If we hit a digit, check surrounding values to see if this is a "valid number".
            if (charAtIndexIsSymbol(idx, data, rowLen)) {
                tempIsValid = true;
                printf(" Valid");
            }
        } else {
            // If we hit a non-digit, process the number stored in the temp buffer.
            // If its a valid number, add it to the sum.
            if (tempIsValid) {
                int result = atoi(temp);
                sum += result;
                printf(" previous number is valid %d, total %d", result, sum);
            }
            // Reset the temp buffer
            memset(temp, '\0', sizeof(temp));
            tempLen = 0;
            tempIsValid = false;
        }
        idx++;
        printf("\n");
    }

    free(data);
    printf("Sum: %d\n", sum);
}