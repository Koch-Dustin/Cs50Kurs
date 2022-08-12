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

    bool score1_is_higher = score1 > score2;
    if (score1_is_higher) {
        printf("Player 1 wins!\n");
        
        return 0;
    }

    bool score2_is_higher = score2 > score1;
    if (score2_is_higher) {
        printf("Player 2 wins!\n");

        return 0;
    }
    
    printf("Tie!\n");
}

int compute_score(string word) {
    int sum_points = 0;
    
    for (int i = 0; i < strlen(word); i++) {
        if (isalpha(word[i])) {
            char number_to_transform_letter_into_uppercase = 'A';
            int current_letter_in_uppercase = toupper(word[i]) - number_to_transform_letter_into_uppercase;
            sum_points += POINTS[current_letter_in_uppercase];
        }
    }

    return sum_points;
}
