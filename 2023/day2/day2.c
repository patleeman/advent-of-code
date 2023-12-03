#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../utils/read.c"

int isNumber(const char* str) {
    if (str == NULL || *str == '\0') {
        return 0;  // Empty string is not a number
    }
    int i = 0;
    // Check for an optional sign (+ or -)
    if (str[i] == '+' || str[i] == '-') {
        i++;
    }
    // Check for digits
    while (str[i] != '\0') {
        if (!isdigit(str[i])) {
            return 0;  // Non-digit character found
        }
        i++;
    }
    return 1;  // All characters are digits (a number)
}

int part1() {
    long fileLen;
    char* input = readFile("day2/data.txt", &fileLen);

    int i = 0;
    int sum_id = 0;
    int sum_power = 0;

    char line[256];
    int len = 0;
    while (input[i] != '\0') {
        if (input[i] == '\n') {
            line[len] = '\0';
            len = 0;

            int temp_game_id = 0;
            int temp_max_green = 0;
            int temp_max_blue = 0;
            int temp_max_red = 0;

            // Process the line, extract the maximum gree, blue, or red value for each line.
            int temp_num = 0;
            char* tokens = strtok(line, ":; ,");
            while (tokens != NULL) {
                if (isNumber(tokens)) {
                    if (temp_game_id == 0) {
                        temp_game_id = atoi(tokens);
                    } else {
                        temp_num = atoi(tokens);
                    }
                }

                if (strcmp(tokens, "green") == 0) {
                    if (temp_num > temp_max_green) {
                        temp_max_green = temp_num;
                    }
                } else if (strcmp(tokens, "blue") == 0) {
                    if (temp_num > temp_max_blue) {
                        temp_max_blue = temp_num;
                    }
                } else if (strcmp(tokens, "red") == 0) {
                    if (temp_num > temp_max_red) {
                        temp_max_red = temp_num;
                    }
                }

                tokens = strtok(NULL, ":; ,");
            }
            printf("Game ID: %d, Max Green: %d (13), Max Blue: %d (14), Max Red: %d (12)\n", temp_game_id, temp_max_green, temp_max_blue, temp_max_red);
            sum_power += temp_max_green * temp_max_blue * temp_max_red;
            if (temp_max_red <= 12 && temp_max_green <= 13 && temp_max_blue <= 14) {
                sum_id += temp_game_id;
                printf("Valid game ID: %d Sum: %d\n", temp_game_id, sum_id);
            }

        } else {
            line[len++] = input[i];
        }
        i++;
    }
    printf("Sum of IDs: %d\n", sum_id);
    printf("Sum of Power: %d\n", sum_power);
    return 0;
}

int main() {
    return part1();
}
