myList = ["A string", 10, 213.55]
print(len(myList))

# indexing and slicing work with list
print(myList[1:])
print(myList[0])

# concatenate
anotherList = [2, "another string"]
newList = myList + anotherList
print(newList)

# METHODS
newList[0] = "A NEW STRING"
print(newList)
newList.append("A new item in our list")
print(newList)
poppedItem = newList.pop()
print(poppedItem)
print(newList)
poppedItem = newList.pop(0)
print(poppedItem)
print(newList)
print('\n\n\n')

newList = ['a', 'z', 't', 'n', 'd']
numList = [123131, 23, 1111, 233, 0, -1231]

newList.sort()
print(newList)
numList.sort()
print(numList)

numList.reverse()
print(numList)
