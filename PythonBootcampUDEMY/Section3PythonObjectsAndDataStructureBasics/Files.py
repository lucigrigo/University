# simple I/O with files
myfile = open('myFile.txt')
print(myfile.read())
print('================')
print(myfile.read())
print('================')
myfile.seek(0)
print(myfile.read())
print('================')
# print(myfile.readlines()) -> WORKS

# opening a file using full file path
# myfile = open("/Users/YourUserName/Documents/FileName.txt")
myfile.close()
# OR
with open('myFile.txt') as myNewFile:
    contents = myNewFile.read()
    print(contents)

# with open('myFile.txt', mode='w') as myNewFile:
# contents = myNewFile.read()
# -> it will not work

print('================')
# supported modes are a, r, w, r+ and w+
with open('myFile.txt', mode='a') as f:
    f.write("hello this is a new line")

with open('myFile.txt') as f:
    print(f.read())

with open('asdsadsadasdasdasdsada.txt', mode='w') as ff:
    ff.write("nothinggggg")

