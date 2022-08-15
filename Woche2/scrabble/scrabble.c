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

    if (score1 > score2) {
        
        printf("Player 1 wins!\n");

        return 0;
    } else if (score1 < score2) {
        printf("Player 2 wins!\n");

        return 0;
    } else {
        printf("Tie!\n");

        return 0;
    }   
}

int compute_score(string word) {
    int sum_points = 0;
    for (int i = 0; i < strlen(word); i++) {

        bool current_letter_is_alphabetic = isalpha(word[i]);
        if (current_letter_is_alphabetic) {
            char current_letter_in_uppercase = toupper(word[i]);
            int numerical_value_of_letter = current_letter_in_uppercase - 'A';
            sum_points += POINTS[numerical_value_of_letter];
        }
    }

    return sum_points;
}
