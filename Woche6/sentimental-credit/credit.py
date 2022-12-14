from cs50 import get_int


def input_number(message):
    while True:
        try:
            user_input = get_int(message)

            if user_input <= 1:
                print("Invalid")
                return

        except ValueError:
            continue
        else:
            return user_input


def check_which_type_card_is():
    if separate_digits % 10 == 0:
        card_is_master_card = count == 16 and (
                first_two_digits == 51
                or first_two_digits == 52
                or first_two_digits == 53
                or first_two_digits == 54
                or first_two_digits == 55
        )

        if card_is_master_card:
            print("MasterCard")
            return

        card_is_american_express = (first_two_digits == 34 or first_two_digits == 37) and count == 15
        if card_is_american_express:
            print("AmericanExpress")
            return

        card_is_visa = (count == 13 or 16) and first_digit == 4
        if card_is_visa:
            print("Visa")
            return

        print("Invalid")

    else:
        print("Invalid 2")


separate_digits = 0
count = 0
divisor = 10


credit_card_number = input_number("Credit Number: ")

workingCC = credit_card_number

while workingCC > 0:
    last_digit = workingCC % 10
    separate_digits = separate_digits + last_digit
    workingCC = workingCC // 100


workingCC = credit_card_number // divisor
while workingCC > 0:
    last_digit = workingCC % 10
    times_two = last_digit * 2
    separate_digits = separate_digits + (times_two % 10) + (times_two // 10)
    workingCC = workingCC // 100

workingCC = credit_card_number
while workingCC != 0:
    workingCC = workingCC // 10
    count += 1


i = 0
while i < count - 2:
    divisor = divisor * 10
    i += 1


first_digit = credit_card_number // divisor
first_two_digits = credit_card_number // (divisor // 10)


check_which_type_card_is()
