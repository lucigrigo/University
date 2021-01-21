# Grigore Lucian-Florin
# Limbaje Formale si Automate
# Tema - Interpretor Glypho

# importing libraries
import sys
import argparse
import collections

# array that will contain indexes for corresponding left and right braces
braces_indexes = []

# executes nop instruction
def gly_nop(stack, instruction_index, base = 10):
    # do nothing
    return instruction_index, stack

# executes input instruction
def gly_input(stack, instruction_index, base = 10):
    # reads number from input and converts him from corresponding base to decimal
    number = int(input(), base)

    # puts newly read number on top of the stack
    stack.append(number)

    return instruction_index, stack

# executes rotation instruction
def gly_rot(stack, instruction_index, base = 10):
    # checking to see if the stack is empty
    # collections.deque().rotate() performs without complain even on an empty stack
    # which does not comply with given task
    if len(stack) != 0:
        stack.rotate()
    else:
        raise Exception

    return instruction_index, stack

# executes swap instruction
def gly_swap(stack, instruction_index, base = 10):
    # pops first and second number from the stack
    first = stack.pop()
    second = stack.pop()

    # puts them back in reversed order
    stack.append(first)
    stack.append(second)

    return instruction_index, stack

# executes push instruction
def gly_push(stack, instruction_index, base = 10):
    # puts new element with value 1 on top of the stack
    stack.append(1)

    return instruction_index, stack

# executes right rotate instruction
def gly_rrot(stack, instruction_index, base = 10):
    # checking to see if the stack is empty
    # collections.deque().rotate() performs without complain even on an empty stack
    # which does not comply with given task
    if len(stack) != 0:
        stack.rotate(-1)
    else:
        raise Exception

    return instruction_index, stack

# executes duplicate instruction
def gly_dup(stack, instruction_index, base = 10):
    # takes out first number from the top of the stack
    number = stack.pop()

    # and puts it back twice
    stack.append(number)
    stack.append(number)

    return instruction_index, stack

# executes addition instruction
def gly_add(stack, instruction_index, base = 10):
    # pops first and second number from the stack
    first = stack.pop()
    second = stack.pop()

    # and puts back their sum
    stack.append(first + second)

    return instruction_index, stack

# executes left brace instruction
def gly_lbrace(stack, instruction_index, base = 10):
    global braces_indexes
    # index to return to in execution order
    to_return = instruction_index

    # taking out first number on the top of the task
    number = stack.pop()

    # if the number is equal to 0, then we jump to the corresponding right brace
    if number == 0:
        for entry in braces_indexes:
            if entry[0] == instruction_index:
                to_return = entry[1]
    
    # we put back the number on the stack
    stack.append(number)

    return to_return, stack

# function that returns character coresponding to a single digit in any base
def digit_to_char(digit):
    if digit < 10:
        return str(digit)
    return chr(ord('A') + digit - 10)

# function that converts a number from decimal into its representation in any base
def str_base(number, base):
    if number < 0:
        return '-' + str_base(-number, base)
    (d, m) = divmod(number, base)
    if d > 0:
        return str_base(d, base) + digit_to_char(m)
    return digit_to_char(m)

# executes output instruction
def gly_output(stack, instruction_index, base = 10):
    # taking out first number of the stack
    number = stack.pop()

    # converting to its representation, if base is not decimal
    if base != 10:
        number = str_base(number = number, base = base)           
    
    # outputing the number
    print(number)

    return instruction_index, stack

# executes multiply instruction
def gly_multiply(stack, instruction_index, base = 10):
    # takes out first and second number from the stack
    first = stack.pop()
    second = stack.pop()

    # and puts back their product
    stack.append(first * second)

    return instruction_index, stack

# executes execute instruction
def gly_execute(stack, instruction_index, base = 10):
    # computing the encoding for the next instruction
    instr = ""
    apps = {}
    free = 0

    # popping the next 4 elements of the stack
    for _ in range(4):
        curr = stack.pop()

        # assigning new numbered digit to the character
        if not curr in apps:
            apps[curr] = free
            free += 1
        
        # appending current digit encoding to instruction string
        instr = instr + str(apps[curr])
    
    # if the instruction is a left or a right brace, we raise and exception
    if instr != "0123" and instr != "0110":
        # executing instruction
        stack = execute_instructions(instructions = [instr], index = instruction_index + 1, stack = stack)
    else:
        raise Exception

    return instruction_index, stack

# executes negate instruction
def gly_negate(stack, instruction_index, base = 10):
    # popping first number from the stack
    number = stack.pop()

    # negating it
    number *= -1

    # and putting it back on the stack
    stack.append(number)

    return instruction_index, stack

# executes pop instruction
def gly_pop(stack, instruction_index, base = 10):
    # popping first number of the stack
    stack.pop()

    return instruction_index, stack

# executes right brace instruction
def gly_rbrace(stack, instruction_index, base = 10):
    global braces_indexes

    # looks for the index of the left brace corresponding to itself
    for entry in braces_indexes:
        if entry[1] == instruction_index:
            return entry[0] - 1, stack
    
    return instruction_index, stack
    
# just-to-be-sure function that exits the program when an invalid instruction code
# is encountered
def gly_invalid_instruction(stack, instruction_index, base = 10):
    print("Invalid instruction code", file=sys.stderr)
    exit(-1)

# function that for a single left brace searches the index of the corresponding right brace
def search_coresp(instructions, index = 0, visited = []):
    global braces_indexes
    while index < len(instructions):
        # if a right brace is encountered
        if instructions[index] == "0123" and not index in visited:
            break
        
        # if a left brace is encountered, it calls itself recursively
        if instructions[index] == "0110" and not index in visited:
            j = search_coresp(instructions = instructions, index = index + 1, visited = visited)
            
            # we reached the end of the instructions and no right brace was found, we exit
            if j == len(instructions):
                print("Error:{}".format(len(instructions)), file=sys.stderr)
                exit(-1)
            
            # we append new found correspondence to our array
            braces_indexes.append([index, j])
            visited.append(index)
            visited.append(j)

        index += 1

    # we return the index of the found right brace
    return index

# function that builds the array that contains the indexes of the corresponding
# left and right braces
def find_braces(instructions, visited = []):
    global braces_indexes

    # we traverse each instruction
    for index, instr in enumerate(instructions):
        # if a left brace is found
        if instr == "0110" and not index in visited:
            # searches the index of the corresponding right brace for the current left brace
            j = search_coresp(instructions = instructions, index = index + 1, visited = visited)
            
            # we reached the end of the instructions and no right brace was found, we exit
            if j == len(instructions):
                print("Error:{}".format(len(instructions)), file=sys.stderr)
                exit(-1)

            # we append new found correspondence to our array
            braces_indexes.append([index, j])
            visited.append(index)
            visited.append(j)
        
        # if a right brace is found, we exit
        if instr == "0123" and not index in visited:
            print("Error:{}".format(index), file=sys.stderr)
            exit(-1)

# function that executes already decoded instructions
def execute_instructions(instructions, stack, index = 0, base = 10):
    # basic initalisations when called first and not from an exec glypho instruction
    if index == 0:
        find_braces(instructions = instructions)

    # encoding to functions correspondences
    switcher = {
        "0000" : gly_nop,
        "0001" : gly_input,
        "0010" : gly_rot,
        "0011" : gly_swap,
        "0012" : gly_push,
        "0100" : gly_rrot,
        "0101" : gly_dup,
        "0102" : gly_add,
        "0110" : gly_lbrace,
        "0111" : gly_output,
        "0112" : gly_multiply,
        "0120" : gly_execute,
        "0121" : gly_negate,
        "0122" : gly_pop,
        "0123" : gly_rbrace
    }
    
    # if it is the main call of the program
    if index == 0:
        # we iterate through all of the instructions
        while index < len(instructions):
            # we get the corresponding function for each instruction
            func = switcher.get(instructions[index], gly_invalid_instruction)

            # we try to execute each instruction, while also being ready to catch any exceptions
            try:
                index, stack = func(stack = stack, instruction_index = index, base = base)
            except:
                print("Exception:{}".format(index), file=sys.stderr)
                exit(-2)
            
            # we go to the next instruction index
            index = index + 1
    else:
        # we simply call the function, without catching any exceptions
        # when this function is called within an execute instruciton
        func = switcher.get(instructions[0], gly_invalid_instruction)
        index, stack = func(stack = stack, instruction_index = index, base = base)

    return stack

# function that builds the glypho specific encoding for a single 4-character string
def decode_single_instr(instruction):
    dec = ""
    apps = {}
    free = 0

    for c in instruction:
        if not c in apps:
            apps[c] = free
            free += 1
        dec = dec + str(apps[c])

    return dec

# function that builds the array of glypho instructions from an array of characters
def decode_instr(instructions):
    decoded = []
    allowed = ""

    # preprocessing the array for making sure it is a valid glypho input
    # taking out any non-available characters
    # and splitting in groups of 4 characters
    for i in range(33, 127):
        allowed = allowed + chr(i)
    for c in instructions:
        if not c in allowed:
            instructions.replace(c, '')
    instructions = [instructions[start:start + 4] for start in range(0, len(instructions), 4)]

    # we decode each instruction
    for instr in instructions:
        decoded.append(decode_single_instr(instr))
    
    return decoded

if __name__ == "__main__":
    # checking number of parameters
    if len(sys.argv) > 3 or len(sys.argv) == 1:
        print("Incorrect number of program arguments", file=sys.stderr)
        exit(-1)

    # parsing input parameters using Argument Parser  
    parser = argparse.ArgumentParser(description="Arguments needed by the program")
    parser.add_argument('input_filename', type=str,
                        help='Path to input file')
    parser.add_argument('base', type=int, nargs='*', default=10,
                        help='Base to compute (default 10)')
    args = vars(parser.parse_args())

    # reading instructions and base
    if isinstance(args['base'], list):
        base = args['base'][0]
    else:
        base = 10
    with open(args['input_filename']) as file:
        instructions = file.read()

    # checking instructions length
    if len(instructions) % 4 != 0:
        print('Error:{}'.format(len(instructions) // 4), file=sys.stderr)
        exit(-1)
    
    # converting each instruction to numerical encoding
    decoded_instructions = decode_instr(instructions)
    
    # executing instructions
    _ = execute_instructions(instructions = decoded_instructions, stack = collections.deque(), base = base)
