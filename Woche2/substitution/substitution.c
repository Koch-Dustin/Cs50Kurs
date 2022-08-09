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

    if(strlen(argv[1]) != 26) {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    for (int i = 0, n = strlen(argv[1]); i < n; i++) {
        if(isalpha(argv[1][i])) {
            count_key_characters++;
        } else if(count_key_characters != strlen(argv[1])) {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }

        
    }

    for(int j = 0, n = strlen(argv[1]); j < n; j++) {
        for(int k = j + 1; k < n; k++) {
            if(tolower(argv[1][j]) == tolower(argv[1][k])) {
                count_repeated_characters++;
            }
            
        }
        
        
        if(count_repeated_characters != 0) {
                printf("Key must not contain repeated characters.\n");
                return 1;
        }
    }

    string plain = get_string("Plainetext: ");

    printf("ciphertext: ");
    for(int w = 0, x = strlen(plain); w < x; w++) {
        if(isalpha(plain[w]) && isupper(plain[w])) {
            int upper = (plain[w] - 65);
            printf("%c", toupper(argv[1][upper]));
        }else if(isalpha(plain[w]) && islower(plain[w])) {
            int lower = (plain[w] - 97);
            printf("%c", tolower(argv[1][lower]));
        }else {
            printf("%c", plain[w]);
        }
    }

    printf("\n");
    return 0;
}