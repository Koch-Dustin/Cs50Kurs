from cs50 import get_string

Text = get_string("Text: ")

letters = 0
for i in Text:
    if ("a" <= i <= "z") or ("A" <= i <= "Z"):
        letters += 1

words = 1
for i in Text:
    if i == " ":
        words += 1

sentences = 0
for i in Text:
    if i == "." or i == "!" or i == "?":
        sentences += 1

L = (letters * (100/words))
s = (sentences * (100 / words))

index = round(((0.0588 * L) - (0.296 * s) - 15.8))

if index < 1:
    print("Before Grade 1")
elif index > 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")
