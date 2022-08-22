#include <cs50.h>
#include <stdio.h>
#include <string.h>

#define MAX 9

typedef struct {
    string name;
    int votes;
}
candidate;

candidate candidates[MAX];

int candidate_count;

bool vote(string name);
void print_winner(void);

int main(int argc, string argv[]) {

    if (argc < 2) {
        printf("Usage: plurality [candidate ...]\n");

        return 1;
    }

    candidate_count = argc - 1;
    if (candidate_count > MAX) {
        printf("Maximum number of candidates is %i\n", MAX);

        return 2;
    }

    for (int i = 0; i < candidate_count; i++) {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    for (int i = 0; i < voter_count; i++) {
        string name = get_string("Vote: ");

        if (!vote(name)) {
            printf("Invalid vote.\n");
        }
    }

    print_winner();
}

bool vote(string name) {
    for (int i = 0; i < candidate_count; i++) {
        bool candidatesname_is_voteable = strcmp(candidates[i].name, name) == 0;
        if (candidatesname_is_voteable) {
            candidates[i].votes++;
            return true;
        }
    }

    return false;
}

void print_winner(void) {
    candidate swap;
    
    for (int i = 0, n = candidate_count; i < n; i++) {
        if (candidates[i].votes > candidates[i + 1].votes) {
            swap = candidates[i];
            candidates[i] = candidates[i + 1]; 
            candidates[i + 1] = swap;
        }

        if(candidates[i].votes == candidates[i + 1].votes) {
            printf("Tie! Between: %s & %s\n", candidates[i].name, candidates[i +1].name);
            return;
        }

    }
    printf("%s\n", candidates[candidate_count].name);
        
    return;
}
