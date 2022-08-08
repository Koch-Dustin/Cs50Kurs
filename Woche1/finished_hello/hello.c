#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string name = get_string("Wie heißt du?: ");
    printf("hello, %s\n", name);
}
