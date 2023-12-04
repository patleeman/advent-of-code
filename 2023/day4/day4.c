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
    // char *data = readFile("day4/test.txt", &fileLen);
    // int num_winning = 5;
    // int num_have = 8;

    char *data = readFile("day4/data.txt", &fileLen);
    int num_winning = 10;
    int num_have = 25;

    // Initialize the array of card counts to 1, so we start with 1 card for each game.
    int i = 0;
    int num_lines = 1;
    while (data[i] != '\0') {
        if (data[i] == '\n') {
            num_lines++;
        }
        i++;
    }
    printf("Number of lines: %d\n", num_lines);
    int card_array[num_lines];
    for (int i = 0; i < num_lines; i++) {
        card_array[i] = 1;
    }

    int idx = 0;
    int sum = 0;
    int row = 0;

    bool processing_winning = false;
    bool processing_have = false;
    int temp_winning[num_winning];
    memset(temp_winning, 0, sizeof(temp_winning));
    int temp_winning_idx = 0;
    int temp_have[num_have];
    memset(temp_have, 0, sizeof(temp_have));
    int temp_have_idx = 0;

    char temp_buffer[3] = {0, 0, '\0'};

    while (data[idx] != '\0') {
        // printf("Char: %c\n", data[idx]);
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
                    // printf("Comparing %d to %d\n", temp_have[i], temp_winning[j]);
                    if (temp_have[i] == temp_winning[j]) {
                        // printf("Found a match: %d\n", temp_have[i]);
                        count++;
                    }
                }
            }
            int score = calculate_score(count);
            sum += score;
            printf("Processed Line. Total Count: %d, Score: %d\n", count, score);
            int current_card_copies = card_array[row];
            for (int j = 0; j < current_card_copies; j++) {
                // Each match increments the next card by 1.
                for (int i = 0; i < count; i++) {
                    int card_num = row + i + 1;
                    printf("Updating card %d\n", card_num);
                    card_array[card_num]++;
                }
            }

            memset(temp_have, 0, sizeof(temp_have));
            memset(temp_winning, 0, sizeof(temp_winning));
            temp_winning_idx = 0;
            temp_have_idx = 0;
            processing_have = false;
            processing_winning = false;

            row++;
        } else {
            // If we hit a :, we are now processing the winning numbers
            if (data[idx] == ':') {
                // printf("Starting to process winning numbers\n");
                processing_winning = true;
                goto next;
            }
            // If we hit a |, we are now processing the have numbers
            if (data[idx] == '|') {
                // printf("Starting to process have numbers\n");
                processing_have = true;
                goto next;
            }
            // Skip spaces
            if (data[idx] == ' ') {
                if (temp_buffer[0] != 0 && processing_have) {
                    // printf("Storing in have array: %d\n", atoi(temp_buffer));
                    temp_have[temp_have_idx] = atoi(temp_buffer);
                    temp_have_idx++;
                } else if (temp_buffer[0] && processing_winning) {
                    // printf("Storing in winning array: %d\n", atoi(temp_buffer));
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
                    // printf("Storing first digit: %c\n", data[idx]);
                    temp_buffer[0] = data[idx];
                } else {
                    // printf("Storing second digit: %c\n", data[idx]);
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

    int total_cards = 0;
    for (int i = 0; i < num_lines; i++) {
        printf("Card %d: %d\n", i + 1, card_array[i]);
        total_cards += card_array[i];
    }
    printf("Total Cards: %d\n", total_cards);

    free(data);
}
