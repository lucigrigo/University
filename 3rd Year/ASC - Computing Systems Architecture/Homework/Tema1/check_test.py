"""
This module checks that the homework's solution output is correct

Computer Systems Architecture Course
Assignment 1
March 2021
"""
import subprocess
import sys


def main():
    if len(sys.argv) != 4:
        print("Invalid number of arguments\nUsage: check_test.py testname output_filepath ref_filepath")
        return

    testname = sys.argv[1]
    output_filename = sys.argv[2]
    ref_filename = sys.argv[3]
    # load the lines from the output file and sort them
    with open(output_filename) as output_file:
        output_lines = output_file.read()

    output_lines = output_lines.split(")")  # sometimes there is no new line between consumer outputs
    output_lines = [line.strip() + ")" for line in output_lines if len(line.strip()) > 0]

    output_lines.sort()

    sorted_output_filename = output_filename + ".sorted"

    # write to input file (tests/{test_name}.in)
    with open(sorted_output_filename, 'w') as sorted_output_file:
        for line in output_lines:
            print(line, file=sorted_output_file)

    command = subprocess.Popen(["diff", sorted_output_filename, ref_filename], stdout=subprocess.PIPE)
    out, err = command.communicate()

    if len(out) == 0:
        print(f"Test {testname}" + ":\t\t" + "PASSED")
    else:
        print(f"Test {testname}" + ":\t\t" + "FAILED")


if __name__ == "__main__":
    main()
