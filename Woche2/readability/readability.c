#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int main(void) {

    string UserText = get_string("Text: ");

    int letters = 0;
    int words = 1;
    int sentences = 0;

    for (int i = 0; i < strlen(UserText); i++) {
        bool character_is_empty = UserText[i] == ' ';
        bool character_is_special = UserText[i] == '.' || UserText[i] == '!' || UserText[i] == '?';
        
        if (isalpha(UserText[i])) {
            letters++;
        } else if (character_is_empty) {
            words++;
        } else if (character_is_special) {
            sentences++;
        }
    }

    float L = (float) letters / (float) words * 100;
    float S = (float) sentences / (float) words * 100;
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    if (index < 1) {
       printf("Before Grade 1\n");
    } else if (index > 16) {
        printf("Grade 16+\n");
    } else {
        printf("Grade %i\n", index);
    }

}
