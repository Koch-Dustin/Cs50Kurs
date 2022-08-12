#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];
bool lock = true;

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{

    if (argc < 2) {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    candidate_count = argc - 1;
    if (candidate_count > MAX) {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++) {
        candidates[i] = argv[i + 1];
    }

    for (int i = 0; i < candidate_count; i++) {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    for (int i = 0; i < voter_count; i++) {

        int ranks[candidate_count];


        for (int j = 0; j < candidate_count; j++) {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks)) {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

bool vote(int rank, string name, int ranks[]) {
    
    for (int i = 0; i < candidate_count; i++) {
        if (strcmp(name,  candidates[i]) == 0) {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

void record_preferences(int ranks[]) {

    for(int i = 0; i < candidate_count; i++) {
        for(int j = i + 1; j < candidate_count; j++) {
            preferences[ranks[i]][ranks[j]] += 1;
        }
    }
    return;
}

void add_pairs(void) {
    
    for (int i = 0; i < candidate_count; i++) {
        for (int j = i + 1; j < candidate_count; j++) {
            if (preferences[i][j] > preferences[j][i]) {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i]) {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
}

void sort_pairs(void) {
    
    for(int i = 0; i < pair_count; i++) {
        int max = i;
        for(int j = i + 1; j < pair_count; j++) {
            bool preference_votes_are_lower_than_maximum_votes = preferences[pairs[j].winner][pairs[j].loser] > preferences[pairs[max].winner][pairs[max].loser];
            if(preference_votes_are_lower_than_maximum_votes) {
                max = j;
            }
        }
        pair temp = pairs[i];
        pairs[i] = pairs [max];
        pairs[max] = temp;
    }
    
    return;
}

bool validateLock(int j) { 
    if (j == 0) {
        return false;
    }

    int rankpoint = 0;
    bool rank[j];
    for (int i = 0; i < j; i++) {
        rank[i] = false;
    }

    validateLock(j - 1);

    for (int i = 0; i < j; i++) {
        for (int k = 0; k < j; k++) {
            if (locked[i][k] == true) {
                rank[i] = true;
            }
        }
    }

    for (int i = 0; i < j; i++) {
        if (rank[i] == true) {
            rankpoint++;
        }
    }

    if (rankpoint == j){
        lock = false;
    }
    return false;
}

void lock_pairs(void) {

    for (int i = 0; i < pair_count; i++) {
        locked[pairs[i].winner][pairs[i].loser] = true;

        validateLock(candidate_count);

        if (!lock) {
            locked[pairs[i].winner][pairs[i].loser] = false;
        }
        lock = true;
    }
}

void print_winner(void) {
    
    int winner;
    int rank;

    for (int i = 0; i < candidate_count; i++) {
        rank = 0;
        for (int k = 0; k < candidate_count; k++) {
            if (locked[k][i] == false) {
                rank++;
            }
        }

        if (rank == candidate_count) {
            printf("%s\n", candidates[i]);
        }
    }
}