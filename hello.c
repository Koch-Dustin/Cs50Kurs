#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string Name = get_string("Wie heißt du?: ");
    printf("hello, %s\n", Name);
}