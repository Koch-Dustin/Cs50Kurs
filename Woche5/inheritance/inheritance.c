#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct person
{
    struct person *parents[2];
    char alleles[2];
}
person;

const int GENERATIONS = 3;
const int INDENT_LENGTH = 4;

person *create_family(int generations);
void print_family(person *personPointer, int generation);
void free_family(person *personPointer);
char random_allele();

int main(void) {

    srand(time(0));

    person *personPointer = create_family(GENERATIONS);

    print_family(personPointer, 0);

    free_family(personPointer);
}

person *create_family(int generations) {

    person *personPointer = malloc(sizeof(person));

    if (generations > 1) {
        personPointer -> parents[0] = create_family(generations - 1);
        personPointer -> parents[1] = create_family(generations - 1);

        personPointer -> alleles[0] = personPointer -> parents[0] -> alleles[rand() % 2];
        personPointer -> alleles[1] = personPointer -> parents[1] -> alleles[rand() % 2];

    } else {
        personPointer -> parents[0] = NULL;
        personPointer -> parents[1] = NULL;

        personPointer -> alleles[0] = random_allele();
        personPointer -> alleles[1] = random_allele();
    }

    return personPointer;
}

void free_family(person *personPointer) {

    if(personPointer == NULL) return;

    free_family(personPointer -> parents[0]);
    free_family(personPointer -> parents[1]);

    free(personPointer);
}

void print_family(person *personPointer, int generation) {
    if (personPointer == NULL) return;

    for (int i = 0; i < generation * INDENT_LENGTH; i++) {
        printf(" ");
    }

    if (generation == 0) {
        printf("Child (Generation %i): blood type %c%c\n", generation, personPointer->alleles[0], personPointer->alleles[1]);
    } else if (generation == 1) {
        printf("Parent (Generation %i): blood type %c%c\n", generation, personPointer->alleles[0], personPointer->alleles[1]);
    } else {
        for (int i = 0; i < generation - 2; i++) {
            printf("Great-");
        }
        printf("Grandparent (Generation %i): blood type %c%c\n", generation, personPointer->alleles[0], personPointer->alleles[1]);
    }

    print_family(personPointer->parents[0], generation + 1);
    print_family(personPointer->parents[1], generation + 1);
}

char random_allele() {
    int randomNumber = rand() % 3;

    if (randomNumber == 0) {
        return 'A';
    } else if (randomNumber == 1) {
        return 'B';
    } else {
        return 'O';
    }
}
