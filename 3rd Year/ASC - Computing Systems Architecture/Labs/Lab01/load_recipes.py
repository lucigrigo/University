"""
	Bonus task: load all the available coffee recipes from the folder 'recipes/'
	File format:
		first line: coffee name
		next lines: resource=percentage

	info and examples for handling files:
		http://cs.curs.pub.ro/wiki/asc/asc:lab1:index#operatii_cu_fisiere
		https://docs.python.org/3/library/io.html
		https://docs.python.org/3/library/os.path.html
"""

import os
import os.path

RECIPES_FOLDER = "recipes"


def import_recipes():
    recipes = {}

    if not os.path.isdir(RECIPES_FOLDER):
        print('Given path is not a folder!')
        return

    for input_file in os.listdir(RECIPES_FOLDER):
        with open(RECIPES_FOLDER + '/' + input_file, 'r') as recipe:
            curr_recipe = {}
            name = recipe.readline()[:-1]

            for line in recipe:
                l = line.split('=')
                l[1] = l[1][:-1]
                curr_recipe[l[0]] = l[1]

            recipes[name] = curr_recipe

    return recipes
