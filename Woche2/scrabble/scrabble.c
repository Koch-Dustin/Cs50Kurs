#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void) {
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    bool Score1IsHigher = score1 > score2;
    if(Score1IsHigher) {
        printf("Player 1 wins!\n");
        return 0;
    }

    bool Score2IsHigher = score2 > score1;
    if(Score2IsHigher) {
        printf("Player 2 wins!\n");
        return 0;
    }
    
    printf("Tie!\n");
}

int compute_score(string word) {
    int sum_points = 0;
    
    for(int i = 0; i < strlen(word); i++) {
        if(isalpha(word[i])) {
            int CurrentLetterInUppercase = toupper(word[i]) - 'A';
            sum_points += POINTS[CurrentLetterInUppercase];
        }
    }

    return sum_points;
}
