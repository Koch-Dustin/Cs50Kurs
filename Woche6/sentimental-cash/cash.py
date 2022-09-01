from cs50 import get_float

coins_count = 0
while True:
    change = get_float("Change owed: ")
    if change > 0:
        break
cent = change * 100

while cent >= 25:
    cent = cent - 25
    coins_count += 1

while cent >= 10:
    cent = cent - 10
    coins_count += 1

while cent >= 5:
    cent = cent - 5
    coins_count += 1

while cent >= 1:
    cent = cent - 1
    coins_count += 1

print(coins_count)
