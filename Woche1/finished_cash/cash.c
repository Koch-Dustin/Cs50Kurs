#include <cs50.h>
#include <stdio.h>

int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void) {
    int cents = get_cents();

    int quarters = calculate_quarters(cents);
    cents = cents - quarters * 25;

    int dimes = calculate_dimes(cents);
    cents = cents - dimes * 10;

    int nickels = calculate_nickels(cents);
    cents = cents - nickels * 5;

    int pennies = calculate_pennies(cents);
    cents = cents - pennies * 1;

    int coins = quarters + dimes + nickels + pennies;

    printf("%i\n", coins);
}

int get_cents(void) {
    int n;

    do {
        n = get_int("Anzahl der Münzen: ");
    } while (n < 0);

    return (n);
}

int calculate_quarters(int cents) {
    int quarter = 25;
    cents = cents / quarter;

    return cents;
}

int calculate_dimes(int cents) {
    int dimes = 10;
    cents = cents / dimes;

    return cents;
}

int calculate_nickels(int cents) {
    int nickels = 5;
    cents = cents / nickels;

    return cents;
}

int calculate_pennies(int cents) {
    int pennies = 1;
    cents = cents / pennies;

    return cents;
}
