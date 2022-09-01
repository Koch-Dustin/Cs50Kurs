from cs50 import get_int


def input_number(message):
    while True:
        try:
            user_input = get_int(message)
        except ValueError:
            continue
        else:
            return user_input


height = get_int("Height: ")
while height < 1 or height > 8:
    height = get_int("Height: ")

for i in range(height):
    print(" " * (height-1-i), end="")
    print("#" * (i+1), end="  ")
    print(" " * (height-1-i))
