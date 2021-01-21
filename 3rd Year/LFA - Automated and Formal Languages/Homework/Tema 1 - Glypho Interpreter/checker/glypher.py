import sys
import string
import random
import os

glyphod = {'n':[0,0,0,0],'i':[0,0,0,1], '>':[0,0,1,0],
        '\\':[0,0,1,1],'1':[0,0,1,2], '<':[0,1,0,0],
        'd':[0,1,0,1], '+':[0,1,0,2], '[':[0,1,1,0],
        'o':[0,1,1,1], '*':[0,1,1,2], 'e':[0,1,2,1],
        '-':[0,1,2,1], '!':[0,1,2,2], ']':[0,1,2,3]}

glyphs = 'ni?>\\1???<d+[o*e-!]'

def gen_b3_string(index):
    if index == 18:
        return [0,1,2,3]
    result = []
    while len(result) < 4:
        result.append(index % 3)
        index //= 3
    return result[::-1]

alphabet = list(map(chr, range(33, 127)))
dna_alphabet = list('actg')
numbers_alphabet = list(string.digits + string.ascii_uppercase)

if __name__ == '__main__':
    for arg in sys.argv[1:]:
        dest = arg.replace('gsh', 'gly')
        if not arg.endswith('gsh') or os.path.isfile(dest):
            print('Skipping {}'.format(arg))
            continue
        with open(arg, 'rt') as f:
            code = ''
            for line in f:
                for c in line:
                    try:
                        i = glyphs.index(c)
                        if c != '?':
                            random.shuffle(alphabet)
                            code += ''.join([alphabet[i] for i in gen_b3_string(i)])
                    except Exception as e:
                        pass
            print(arg, code)
            with open(dest, 'wt') as g:
                g.write(code)
