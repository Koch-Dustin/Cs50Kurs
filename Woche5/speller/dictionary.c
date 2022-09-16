#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <stdint.h>
#include <ctype.h>
#include "dictionary.h"

typedef struct node {
    char word[LENGTH + 1];
    struct node *next;
}
node;

const unsigned int N = 65536;

node *table[N];

int total_words = 0;

bool check(const char *word) {
    int len = strlen(word);
    char lword[len + 1];
    for (int i = 0; i < len; i++) {
        lword[i] = tolower(word[i]);
    }

    lword[len] = '\0';

    int index = hash(lword);
    node *cursor = table[index];

    while (cursor != NULL) {
        if (strcasecmp(cursor->word, word) != 0) {
            cursor = cursor->next;
        } else return true;
    }

    return false;
}

unsigned int hash(const char *word) {
    unsigned int hash = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
        hash = (hash << 2) ^ word[i];

    return hash % N;
}

bool load(const char *dictionary) {
    FILE *file = fopen(dictionary, "r");
    if (!file) return false;

    char buffer[LENGTH + 1];

    while(fscanf(file, "%s", buffer) != EOF) {
        node *n = malloc(sizeof(node));

        strcpy(n->word, buffer);

        unsigned int index = hash(buffer);

        if (table[index] != NULL) {
           n->next = table[index];
        } else {
            n->next = NULL;
        }

        table[index] = n;
        total_words++;
    }

    fclose(file);

    return true;
}

unsigned int size(void) {
    return total_words;
}

void destroy(node *root) {
    if (root -> next != NULL) {
        destroy(root->next);
    }
    free(root);
    
    return;
}

bool unload(void) {
    for (int i = 0; i < N; i++) {
        if (table[i]!= NULL) {
            destroy(table[i]);
            return true;
        } else {
            return false;
        }
    }
}
