# sets are unordered collections of unique elements
mySet = set()
mySet.add("a")
mySet.add("b")
mySet.add("c")
print(mySet)
mySet.add("c")
print(mySet)

myList = [1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3]
newSet = set(myList)
print(newSet)
