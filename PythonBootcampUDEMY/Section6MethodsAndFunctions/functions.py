def halo(name='NAME'):
    '''
     DOCUMENTATION FOR THE FUNCTION
     bla bla bla
    '''
    print("hello " + name)


help(halo)
halo("luci")
halo()


def dog_check(sstring):
    # if  'dog' in sstring.lower():
    #     return True
    # else:
    #     return False
    return 'dog' in sstring.lower()


print(dog_check("asiodjasdpadogoiasjddsaoijas"))
print(dog_check("DOG"))


def pig_latin(word):
    first_letter = word[0]
    if first_letter in 'aeious':
        pig_word = word + 'ay'
    else:
        pig_word = word[1:] + first_letter + 'ay'
    return pig_word
