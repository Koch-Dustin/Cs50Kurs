#include <cs50.h>
#include <stdio.h>
#include <string.h>

#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

int preferences[MAX_VOTERS][MAX_CANDIDATES];

typedef struct {
    string name;
    int votes;
    bool eliminated;
}
candidate;

candidate candidates[MAX_CANDIDATES];

int voter_count;
int candidate_count;

void eliminate(int min);
void tabulate(void);
int find_min(void);
bool is_tie(int min);
bool print_winner(void);
bool vote(int voter, int rank, string name);

int main(int argc, string argv[]) {
    if (argc < 2) {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES) {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }

    for (int i = 0; i < candidate_count; i++) {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS) {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    for (int i = 0; i < voter_count; i++) {
        for (int j = 0; j < candidate_count; j++) {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(i, j, name)) {
                printf("Invalid vote.\n");
                return 4;
            }
        }
        printf("\n");
    }

    while (true) {
        tabulate();

        bool won = print_winner();
        if (won) {
            break;
        }
        
        int voted_person_with_the_least_votes = find_voted_person_with_the_least_votes();
        bool tie = is_tie(voted_person_with_the_least_votes);

        if (tie) {
            for (int i = 0; i < candidate_count; i++) {
                if (!candidates[i].eliminated) {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        eliminate(voted_person_with_the_least_votes);

        for (int i = 0; i < candidate_count; i++) {
            candidates[i].votes = 0;
        }
    }

    return 0;
}

bool vote(int voter, int rank, string name) {
    for (int i = 0; i < candidate_count; i++) {
        bool voted_person_is_in_candidates_list = strcmp(name, candidates[i].name) == 0; 
        if (voted_person_is_in_candidates_list) {
            preferences[voter][rank] = i;
            return true;
        }
    }

    return false;
}

void tabulate(void) {
    for (int i = 0; i < voter_count; i++) {
        for (int j = 0; j < candidate_count; j++) {
           int candidate_index = preferences[i][j];

           if (candidates[candidate_index].eliminated == false) {
               candidates[candidate_index].votes++;
               break;
           }
        }
    }

    return;
}

bool print_winner(void) {
    int half_vote = voter_count / 2;
    for (int i = 0; i < voter_count; i++) {  
        if (candidates[i].votes > half_vote) {
            printf("%s\n", candidates[i].name);
            return true; 
        }
    }

    return false;
}

int find_voted_person_with_the_least_votes(void) {
    int minimal_vote = MAX_VOTERS; 

    for (int i = 0; i < candidate_count; i++) {
        if (candidates[i].eliminated == false && candidates[i].votes < minimal_vote) {
            minimal_vote = candidates[i].votes;
        }
    }

    return minimal_vote;
}

bool is_tie(int voted_person_with_the_least_votes) {
    for (int i = 0; i < candidate_count; i++) {
        bool candidate_is_not_eliminated_or_has_the_least_votes = candidates[i].eliminated == false && candidates[i].votes != voted_person_with_the_least_votes;
        if (candidate_is_not_eliminated_or_has_the_least_votes) {
            return false;
        }
    }

    return true;
}

void eliminate(int voted_person_with_the_least_votes) {
    for (int i = 0; i < candidate_count; i++) {
        if (candidates[i].votes == voted_person_with_the_least_votes) {
            candidates[i].eliminated = true;
        }
    }

    return;
}
