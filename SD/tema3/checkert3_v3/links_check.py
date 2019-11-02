import sys

def read_input_file(filename):
  with open(filename, 'r') as f:
    lines = f.readlines()

    first_line = lines[0].split()
    n = int(first_line[0])
    m = int(first_line[1])

    index = 1
    
    orase = []
    centrale = []

    for i in range(n):
      coordonate = lines[index].split()
      orase.append((int(coordonate[0]), int(coordonate[1])))
      index += 1

    for i in range(m):
      coordonate = lines[index].split()
      centrale.append((int(coordonate[0]), int(coordonate[1])))
      index += 1

    return n, m, orase, centrale


def read_output_file(filename):
  with open(filename, 'r') as f:
    lines = f.readlines()

    indexes = []

    for line in lines:
      indexes.append(int(line))

    return indexes


def read_correct_file(filename):
  with open(filename, 'r') as f:
    lines = f.readlines()

    return int(lines[0])



if __name__ == "__main__":
  input_filename = sys.argv[1]
  output_filename = sys.argv[2]
  correct_filename = sys.argv[3]

  n, m, orase, centrale = read_input_file(input_filename)
  index_centrale = read_output_file(output_filename)
  cuplaj = read_correct_file(correct_filename)

  if len(index_centrale) != n:
    print("In fisierul de iesire nu exista N linii")
    exit(1)

  suma = 0
  for index, oras in enumerate(orase):
    d = abs(oras[0] - centrale[index_centrale[index]][0]) + abs(oras[1] - centrale[index_centrale[index]][1])
    suma += d

  if suma == cuplaj:
    exit(0)
  else:
    print("Cuplajul minim era " + str(cuplaj) + ". Tu ai obtinut " + str(suma) + ".")
    exit(1)
