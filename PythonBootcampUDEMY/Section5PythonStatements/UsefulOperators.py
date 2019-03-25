for num in range(0, 10, 2):
    print(num)

# indexCount = 0

# for letter in 'abcde':
#     print(f'At index {indexCount} the letter is {letter}')
#     indexCount += 1

# enumerate()
word = 'abcdef'
for index, value in enumerate(word):
    print('\n\n')
    print(index)
    print(value)

# zip()
myList = [1, 2, 3, 4, 5]
mySecondList = ['a', 'b', 'c']
myThirdList = [100, 200, 300]
for item in zip(myList, mySecondList, myThirdList):
    print(item)

# in
print(1 in [1, 2, 3])
print('x' in ['a', 'b', 'c'])

# min() and max()

from random import shuffle

list = [1, 2, 3, 4, 5, 6]
shuffle(list)
print(list)

from random import randint

print(randint(0, 100))

name = input("What is your name?")
print(f"Hello {name}")
