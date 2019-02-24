def square(num):
    return num ** 2


my_nums = [1, 2, 3, 4, 5]
for item in map(square, my_nums):
    print(item)


def splicer(sstring):
    if len(sstring) % 2 == 0:
        return 'even'
    else:
        return sstring[0]


names = ['Luci', 'Alex', 'Edi', 'MIu bossu']
print(list(map(splicer, names)))


def is_even(n):
    return n % 2 == 0


numbers = [1, 2, 3, 4, 5]
for item in filter(is_even, numbers):
    print(item)


def square(n):
    return n ** 2


function = lambda b: b ** 2
print(function(25))

for i in map(lambda a: a ** 3, [1, 2, 3, 4, 5]):
    print(i)
