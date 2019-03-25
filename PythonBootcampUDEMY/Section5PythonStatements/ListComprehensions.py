myString = 'hello'

# beginner move
# myList = []
# for letter in myString:
#     myList.append(letter)
# print(myList)

myList = [letter for letter in myString]
print(myList)

myList = [x ** 2 for x in range(0, 10)]
print(myList)

myList = [x for x in range(0, 11) if x % 2 == 0]
print(myList)

celsius = [0, 10, 20, 34.5]
fahrenheit = [((9 / 5) * temp + 32) for temp in celsius]
print(fahrenheit)

results = ['EVEN' if x % 2 == 0 else 'ODD' for x in range(0, 11)]
print(results)

list = []
for x in [2, 3, 5]:
    for y in [100, 200, 300]:
        list.append(x * y)
print(list)

list = [x * y for x in range(1, 10) for y in [1, 10, 1000]]
print(list)
