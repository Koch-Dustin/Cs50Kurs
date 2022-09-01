from cs50 import get_int


def input_number(message):
    while True:
        try:
            user_input = int(input(message))
        except ValueError:
            continue
        else:
            return user_input


height = input_number("Height: ")
while height < 1 or height > 8:
    height = int(input("Height: "))

for i in range(height):
    print(" " * (height-1-i), end="")
    print("#" * (i+1), end="  ")
    print("#" * (i+1), end="")
    print(" " * (height-1-i))
