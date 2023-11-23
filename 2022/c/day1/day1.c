#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *fp;
    fp = fopen("data.txt", "r");
    if (fp == NULL) {
        printf("File not found");
    }

    int max = 0;
    int temp = 0;
    char line[30];
    while (fgets(line, sizeof(line), fp)) {
        size_t len = strlen(line);
        if (line[len - 1] == '\n') {
            line[len - 1] = '\0';
            len--;
        }

        // If it's am empty line
        if (len <= 0) {
            if (temp > max) {
                max = temp;
            }
            temp = 0;
            continue;
        }
        
        int calories = atoi(line);
        if (calories != 0 || strcmp(line, "0") == 0) {
            temp += calories;
        } else {
            printf("Invalid number: %s\n", line);
        }
    }

    fclose(fp);
    printf("Max calories: %d\n", max);
}
