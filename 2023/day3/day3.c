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

int part1() {
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
    return 0;
}

int getGearRatios(int index, char *data, int rowLen) {
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

    int ratioOne = 0;
    int ratioTwo = 0;

    for (int i = 0; i < 8; i++) {
        if (indicies[i] < 0 || indicies[i] > strlen(data)) {
            continue;
        }
        char c = data[indicies[i]];
        if (isdigit((unsigned char)c)) {
            printf("index: %d, char: %c\n", indicies[i], c);
            // Scan forward
            char front[10] = "";
            char tempStr[2] = {c, '\0'};
            strcat(front, tempStr);
            int j = indicies[i] + 1;
            while (isdigit(data[j])) {
                char tempStr[2] = {data[j], '\0'};
                strcat(front, tempStr);
                j++;
            }
            // Scan backwards
            char back[10] = "";
            j = indicies[i] - 1;
            while (isdigit(data[j])) {
                char tempStr[2] = {data[j], '\0'};
                strcat(back, tempStr);
                j--;
            }
            // Reverse the back string
            char reversed[10] = "";
            int k = 0;
            for (int j = strlen(back) - 1; j >= 0; j--) {
                reversed[k++] = back[j];
            }
            // Concat the front and back strings
            strcat(reversed, front);
            reversed[strlen(reversed)] = '\0';
            printf("reversed: %s\n", reversed);
            // Convert the temp array to an int
            int result = atoi(reversed);
            // If a number gets scanned more than once, skip it.
            if (result == ratioOne || result == ratioTwo) {
                continue;
            }
            if (ratioOne == 0) {
                ratioOne = result;
            } else if (ratioTwo == 0) {
                ratioTwo = result;
            } else {
                printf("Error: more than 2 ratios found\n");
                exit(1);
            }
        }
    }

    if (ratioOne != 0 && ratioTwo != 0) {
        printf("ratios: %d * %d = %d\n", ratioOne, ratioTwo, ratioOne * ratioTwo);
        return ratioOne * ratioTwo;
    }

    return 0;
}

int part2() {
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

        if (data[idx] == '*') {
            sum += getGearRatios(idx, data, rowLen);
        }
        idx++;
        printf("\n");
    }

    free(data);
    printf("Sum: %d\n", sum);
    return 0;
}

int main() {
    // part1();
    return part2();
}