myList = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
for a in myList:
    # Check for even
    if a % 2 == 0:
        print(a)
    else:
        print(f"Odd number: {a}")

listSum = 0
for a in myList:
    listSum += a
print(listSum)

string = "Hello Lucian"
for letter in string:
    print(letter)
for _ in string:
    print("LETTER")

# tuple unpacking
myList = [(1, 2), (3, 4), (5, 6), (7, 8)]
for a, b in myList:
    # print(a)
    print(b)

d = {'k1': 1, 'k2': 2, 'k3': 3}
for key, value in d.items():
    print(key)
    print(value)
