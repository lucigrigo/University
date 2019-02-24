def print_map(map):
    print(map[7] + ' | ' + map[8] + ' | ' + map[9])
    print(map[4] + ' | ' + map[5] + ' | ' + map[6])
    print(map[1] + ' | ' + map[2] + ' | ' + map[3])


def create_map():
    list = []
    for i in range(1, 11):
        list.append(' ')
    return list


def check_end(map):
    # teste pentru linii complete, coloane complete sau diagonale complete
    # multi indici ... :(
    # care rezulta True daca jocul se termina si un player castiga
    return False


game_table = []
game_table = create_map()
x = int(input("enter position:\n"))
if x in range(1, 9):
    game_table[x] = 'X'
    print(x)
else:
    print("wrong number!\n")

print_map(game_table)
