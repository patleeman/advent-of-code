#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void part1()
{
    FILE *fp;
    fp = fopen("data.txt", "r");
    if (fp == NULL)
    {
        printf("File not found");
    }

    int max = 0;
    int temp = 0;
    char line[30];
    while (fgets(line, sizeof(line), fp))
    {
        size_t len = strlen(line);
        if (line[len - 1] == '\n')
        {
            line[len - 1] = '\0';
            len--;
        }

        // If it's am empty line
        if (len <= 0)
        {
            if (temp > max)
            {
                max = temp;
            }
            temp = 0;
            continue;
        }

        int calories = atoi(line);
        if (calories != 0 || strcmp(line, "0") == 0)
        {
            temp += calories;
        }
        else
        {
            printf("Invalid number: %s\n", line);
        }
    }

    fclose(fp);
    printf("Max calories: %d\n", max);
}

int compare(const void *a, const void *b)
{
    return (*(int *)b - *(int *)a);
}

void part2()
{
    FILE *fp;
    fp = fopen("data.txt", "r");
    if (fp == NULL)
    {
        printf("File not found");
    }

    int *calories = (int *)malloc(50 * sizeof(int));
    int size = 0;
    if (calories == NULL)
    {
        printf("Failed to allocate memory");
        exit(1);
    }

    int temp = 0;
    char line[30];
    while (fgets(line, sizeof(line), fp))
    {
        size_t len = strlen(line);
        if (line[len - 1] == '\n')
        {
            line[len - 1] = '\0';
            len--;
        }

        // If it's am empty line save to the array
        if (len <= 0)
        {
            calories[size] = temp;
            size++;
            temp = 0;
            continue;
        }

        int calories = atoi(line);
        if (calories != 0 || strcmp(line, "0") == 0)
        {
            temp += calories;
        }
        else
        {
            printf("Invalid number: %s\n", line);
        }
    }
    for (int i = 0; i < sizeof(calories); i++)
    {
        printf("%d\n", calories[i]);
    }
    qsort(calories, size, sizeof(int), compare);
    int sum = calories[0] + calories[1] + calories[2];
    printf("Sum: %d\n", sum);

    fclose(fp);
    free(calories);
}

int main()
{
    part1();
    part2();
}