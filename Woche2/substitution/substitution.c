#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[]) {

    int count_key_characters = 0;
    int count_repeated_characters = 0;

    if (argc != 2) {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    if (strlen(argv[1]) != 26) {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    for (int i = 0, n = strlen(argv[1]); i < n; i++) {
        bool current_letter_is_alphabetic = isalpha(argv[1][i]);
                
        if (!current_letter_is_alphabetic) {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }
        
        count_key_characters++;
    }

    for (int j = 0, n = strlen(argv[1]); j < n; j++) {
        for (int k = j + 1; k < n; k++) {
            int character_to_lower = argv[1][j]; 
            if (tolower(character_to_lower) == tolower(character_to_lower)) {
                printf("Key must not contain repeated characters.\n");
                return 1;
            }
        }
    }

    string plain = get_string("Plaintext: ");
 
    printf("ciphertext: ");
    for (int w = 0, x = strlen(plain); w < x; w++) {
        bool character_is_uppercase = isupper(plain[w]);
        bool character_is_lowercase = islower(plain[w]);
        
        
        if (character_is_uppercase) {
            int upper = (plain[w] - 65);
            printf("%c", toupper(argv[1][upper]));
        } else if(character_is_lowercase) {
            int lower = (plain[w] - 97);
            printf("%c", tolower(argv[1][lower]));
        } else {
            printf("%c", plain[w]);
        }
    }
    printf("\n");

    return 0;
}
