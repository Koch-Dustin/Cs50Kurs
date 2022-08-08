#include <cs50.h>
#include <stdio.h>

int main(void) {
    long ccard;
    long divisor = 10;

    do {
        ccard = get_long_long("Credit: ");
    } while (ccard <= 0);
    
    long workingCC = ccard;
    int sum = 0;
    int count = 0;

    while (workingCC > 0) {
        int lastDigit = workingCC % 10;
        sum = sum + lastDigit; 
        workingCC = workingCC / 100;
    }

    workingCC = ccard / 10;
    while (workingCC > 0) {
        int lastDigit = workingCC % 10;
        int timesTwo = lastDigit * 2;
        sum = sum + (timesTwo % 10) + (timesTwo / 10);
        workingCC = workingCC / 100;
    }

    workingCC = ccard;
    while (workingCC != 0) {
        workingCC = workingCC / 10;
        count++;
    }
    
    for (int i = 0; i < count - 2; i++) {
        divisor = divisor * 10;
    }

    int firstDigit = ccard / divisor;
    int firstTwoDigits = ccard / (divisor / 10); 

    if (sum % 10 == 0) {

        bool CardIsMasterCard = count == 16 && (firstTwoDigits == 51 || firstTwoDigits == 52 || firstTwoDigits == 53 || firstTwoDigits == 54 || firstTwoDigits == 55);
        if(CardIsMasterCard) {
            printf("MasterCard\n");
            return 0;
        }
        
        bool CardIsAmericanExpress = (firstTwoDigits == 34 || firstTwoDigits == 37) && count == 15;
        if(CardIsAmericanExpress) {
            printf("AmericanExpress\n");
            return 0;
        }
        
        bool CardIsVisa = (count == 13 || count == 16) && firstDigit == 4;
        if(CardIsVisa) {
            printf("Visa\n");
            return 0;
        }

        printf("Invalid\n");

    } else {
        printf("Invalid\n");
    }
}
