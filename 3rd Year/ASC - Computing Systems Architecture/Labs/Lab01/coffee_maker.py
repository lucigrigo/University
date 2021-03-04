"""
A command-line controlled coffee maker.
"""

import sys
from load_recipes import import_recipes

"""
Implement the coffee maker's commands. Interact with the user via stdin and print to stdout.

Requirements:
    - use functions
    - use __main__ code block
    - access and modify dicts and/or lists
    - use at least once some string formatting (e.g. functions such as strip(), lower(),
    format()) and types of printing (e.g. "%s %s" % tuple(["a", "b"]) prints "a b"
    - BONUS: read the coffee recipes from a file, put the file-handling code in another module
    and import it (see the recipes/ folder)

There's a section in the lab with syntax and examples for each requirement.

Feel free to define more commands, other coffee types, more resources if you'd like and have time.

Tips:
*  Start by showing a message to the user to enter a command, remove our initial messages
*  Keep types of available coffees in a data structure such as a list or dict
e.g. a dict with coffee name as a key and another dict with resource mappings (resource:percent)
as value
"""

# Commands
EXIT = "exit"
LIST_COFFEES = "list"
# !!! when making coffee you must first check that you have enough resources!
MAKE_COFFEE = "make"
HELP = "help"
REFILL = "refill"
RESOURCE_STATUS = "status"
commands = [EXIT, LIST_COFFEES, MAKE_COFFEE, REFILL, RESOURCE_STATUS, HELP]

# Coffee examples
ESPRESSO = "espresso"
AMERICANO = "americano"
CAPPUCCINO = "cappuccino"

# Resources examples
WATER = "water"
COFFEE = "coffee"
MILK = "milk"

# Coffee maker's resources - the values represent the fill percents
RESOURCES = {WATER: 100, COFFEE: 100, MILK: 100}

# reading recipes from file
recipes = import_recipes()

"""
Example result/interactions:

I'm a smart coffee maker
Enter command:
list
americano, cappuccino, espresso
Enter command:
status
water: 100%
coffee: 100%
milk: 100%
Enter command:
make
Which coffee?
espresso
Here's your espresso!
Enter command:
refill
Which resource? Type 'all' for refilling everything
water
water: 100%
coffee: 90%
milk: 100%
Enter command:
exit
"""


def f_list_coffees():
    print('Available coffee types:')

    for coffee in recipes.keys():
        print(f"\t- {coffee}")


def f_make_coffee():
    coffee = input('Which coffee? ')

    if coffee not in recipes.keys():
        print('Invalid coffee type')
        return

    recipe = recipes.get(coffee)
    ok = True

    for resource, quantity in recipe.items():
        if RESOURCES[resource] < int(quantity):
            print(
                'Not enough {}. Consider refilling me sometimes :('.format(resource))
            ok = False

    if not ok:
        return

    for resource, quantity in recipe.items():
        RESOURCES[resource] = RESOURCES[resource] - int(quantity)

    print('Here\'s your %s!' % coffee)


def f_help():
    print('Commands available:')
    print('\t- \'exit\' - close the program')
    print('\t- \'list\' - list available coffees')
    print('\t- \'make\' - brew coffee')
    print('\t- \'help\' - list all available commands')
    print('\t- \'refill\' - refill one or more resources')
    print('\t- \'status\' - show current status of all the resources')


def f_refill():
    resource = input('Which resource? Type \'all\' for refilling everything: ')

    if resource == 'all':
        RESOURCES[WATER] = 100
        RESOURCES[MILK] = 100
        RESOURCES[COFFEE] = 100
    elif resource == COFFEE:
        RESOURCES[COFFEE] = 100
    elif resource == MILK:
        RESOURCES[MILK] = 100
    elif resource == WATER:
        RESOURCES[WATER] = 100

    if resource != 'all' and resource != WATER and resource != MILK and resource != COFFEE:
        print('Invalid resource! Try again...')
    else:
        print('Refill successful! New status of the resources:')
        f_resource_status()


def f_resource_status():
    print('Available resources:')

    for resource, percentage in RESOURCES.items():
        print(f'\t- {resource}: {percentage}%')


def f_invalid_cmd():
    print('You entered an invalid command! Please use a valid command:')
    f_help()


f_commands = {
    LIST_COFFEES: f_list_coffees,
    MAKE_COFFEE: f_make_coffee,
    HELP: f_help,
    REFILL: f_refill,
    RESOURCE_STATUS: f_resource_status
}

if __name__ == '__main__':
    print("I'm a smart coffee maker!")

    while True:
        cmd = input("Enter command: ")

        if cmd == EXIT:
            print('Exiting program')
            break

        f_cmd = f_commands.get(cmd, f_invalid_cmd)

        f_cmd()
