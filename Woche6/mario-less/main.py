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


i = 0
while i < height:
    spacing = height-1
    block = 0
    while spacing >= i:
        print(" ", end="")
        spacing -= 1
    while block <= i:
        print("#", end="")
        block += 1
    print("")
    i += 1
