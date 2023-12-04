#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../utils/read.h"

int calculate_score(int n) {
    if (n <= 0) {
        return 0;
    }
    return pow(2, n - 1);
}

int main() {
    long fileLen;
    char *data = readFile("day4/data.txt", &fileLen);

    int idx = 0;
    int sum = 0;

    bool processing_winning = false;
    bool processing_have = false;
    int num_winning = 10;
    int num_have = 25;
    int temp_winning[num_winning];
    memset(temp_winning, 0, sizeof(temp_winning));
    int temp_winning_idx = 0;
    int temp_have[num_have];
    memset(temp_have, 0, sizeof(temp_have));
    int temp_have_idx = 0;

    char temp_buffer[3] = {0, 0, '\0'};

    while (data[idx] != '\0') {
        printf("Char: %c\n", data[idx]);
        if (data[idx] == '\n') {
            // Process the last number in the buffer
            if (temp_buffer[0] != 0 && processing_have) {
                printf("Storing in have array: %d\n", atoi(temp_buffer));
                temp_have[temp_have_idx] = atoi(temp_buffer);
                temp_have_idx++;
            } else if (temp_buffer[0] && processing_winning) {
                printf("Storing in winning array: %d\n", atoi(temp_buffer));
                temp_winning[temp_winning_idx] = atoi(temp_buffer);
                temp_winning_idx++;
            }
            temp_buffer[0] = 0;
            temp_buffer[1] = 0;

            // Do comparisons and calculate score.
            int count = 0;
            for (int i = 0; i < num_have; i++) {
                for (int j = 0; j < num_winning; j++) {
                    printf("Comparing %d to %d\n", temp_have[i], temp_winning[j]);
                    if (temp_have[i] == temp_winning[j]) {
                        printf("Found a match: %d\n", temp_have[i]);
                        count++;
                    }
                }
            }
            int score = calculate_score(count);
            sum += score;
            printf("Processed Line. Total Count: %d, Score: %d\n", count, score);

            memset(temp_have, 0, sizeof(temp_have));
            memset(temp_winning, 0, sizeof(temp_winning));
            temp_winning_idx = 0;
            temp_have_idx = 0;
            processing_have = false;
            processing_winning = false;
        } else {
            // If we hit a :, we are now processing the winning numbers
            if (data[idx] == ':') {
                printf("Starting to process winning numbers\n");
                processing_winning = true;
                goto next;
            }
            // If we hit a |, we are now processing the have numbers
            if (data[idx] == '|') {
                printf("Starting to process have numbers\n");
                processing_have = true;
                goto next;
            }
            // Skip spaces
            if (data[idx] == ' ') {
                if (temp_buffer[0] != 0 && processing_have) {
                    printf("Storing in have array: %d\n", atoi(temp_buffer));
                    temp_have[temp_have_idx] = atoi(temp_buffer);
                    temp_have_idx++;
                } else if (temp_buffer[0] && processing_winning) {
                    printf("Storing in winning array: %d\n", atoi(temp_buffer));
                    temp_winning[temp_winning_idx] = atoi(temp_buffer);
                    temp_winning_idx++;
                }
                temp_buffer[0] = 0;
                temp_buffer[1] = 0;
                goto next;
            }
            // Skip the first few characters until the winning numbers
            if (!processing_have && !processing_winning) {
                goto next;
            }
            // For each digit, store it in a temp buffer, then when it fills up, dump that into the appropriate array.
            if (isdigit(data[idx])) {
                // Store the first digit in the buffer.
                if (temp_buffer[0] == 0) {
                    printf("Storing first digit: %c\n", data[idx]);
                    temp_buffer[0] = data[idx];
                } else {
                    printf("Storing second digit: %c\n", data[idx]);
                    // Once we have the 2nd digit, process it and dump it in the array, then reset.
                    temp_buffer[1] = data[idx];
                }
            }
        }
        printf("\n");
    next:
        idx++;
    }
    printf("Sum: %d\n", sum);

    free(data);
}
