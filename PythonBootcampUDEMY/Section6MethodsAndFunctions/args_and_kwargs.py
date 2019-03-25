# returns back a tuple
def myfunc(*args):
    return sum(args) * 0.05


print(myfunc(10, 10, 10, 10, 10, 10, 10, 10, 10, 10))


# returns back a dictionary
def mysecondfunc(**kwargs):
    if 'fruit' in kwargs:
        print('My fruit of choise is {}.'.format(kwargs['fruit']))
    else:
        print('i am sad')


mysecondfunc(fruit='apple')


def stupidfunc(*args, **kwargs):
    print('I would like {} {}.'.format(args[0], kwargs['food']))


stupidfunc(10, 20, 30, food='sarmale')
word = 'asdsada'


def abla(cuvant):
    final_word = ''
    for i in range(len(cuvant)):
        if i % 2 == 0:
            final_word += cuvant[i].upper()
        else:
            final_word += cuvant[i].lower()
    return final_word

# print(abla('asdkasdlas'))

kk = abla('asdsad')
print(kk)