myString = "I have no idea what i'm doing ..."
print(myString)
print(len(myString))

# indexing
print(myString[3] + '\n' + myString[10])

# there is also reverse indexing
print(myString[-5])

# slicing
myString = 'abcdefghijk'
print(myString[2])
print(myString[2:])
print(myString[:3])
print(myString[::])
print(myString[::2])
print(myString[::-1])

# immutability
# concatenation

letter = 'z'
letter *= 10
print(letter)

# methods
x = "Hello World"
print(x.split("o"))
print(x.split())

# .format() method for print
print("Hello {}".format("Lucian"))
print("The {1} {0} {2}.".format("brown", "quick", "fox"))

# string literal formatting
name = "Lucian"
print(f"Hello, his name is {name}")
age = 5
print(f"{name} is {age} years old.")
