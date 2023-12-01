#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getScore(char c)
{
    switch (c)
    {
    case 'A':
    case 'X':
        return 1;
    case 'B':
    case 'Y':
        return 2;
    case 'C':
    case 'Z':
        return 3;
    default:
        printf("Invalid character: %c\n", c);
    }
}

void part1()
{
    FILE *fp;
    fp = fopen("data.txt", "r");
    if (fp == NULL)
    {
        printf("File not found");
    }

    int opponent_score = 0;
    int self_score = 0;
    char line[10];
    while (fgets(line, sizeof(line), fp))
    {
        char opponent = line[0];
        int os = getScore(opponent);
        opponent_score += getScore(opponent);
        printf("Opponent: %c, Score: %d\n", opponent, opponent_score);

        char self = line[2];
        int ss = getScore(self);
        self_score += ss;
        printf("Self: %c, Score: %d\n", self, self_score);

        if (ss > os)
        {
            self_score += 6;
        }
        else if (ss < os)
        {
            opponent_score += 6;
        }
        else
        {
            self_score += 3;
            opponent_score += 3;
        }
    }
    printf("Self score: %d\n", self_score);
    printf("Opponent score: %d\n", opponent_score);
}

void part2()
{
}

int main()
{
    part1();
    part2();
}