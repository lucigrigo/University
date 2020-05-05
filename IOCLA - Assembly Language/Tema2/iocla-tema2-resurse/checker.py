#!/usr/bin/env python3

import subprocess
import shutil
import os
import sys

runExec = "./tema2"
useShell = True

numTasks = 6
tasksWithARGV = [3, 4, 5]
pointsPerTask = [3, 2, 3, 4, 3, 3]

pointsScored = 0

header = "======================= Tema 2 IOCLA ======================="
print("\n" + header + "\n")

if not os.path.exists(runExec):
    rc = subprocess.call("make", shell=useShell)
    if rc != 0:
        sys.stderr.write("make failed with status %d\n" % rc)
        sys.exit(rc)

if not os.path.exists(runExec):
    sys.stderr.write("The file %s is missing and could not be created with make" % runExec)
    sys.exit(-1)

for n in range(1, numTasks + 1):

    for t in range(1, 6):
        args = ""
        if n in tasksWithARGV:
            with open('inputs/task' + str(n) + "_" + str(t) + "_args") as f:
                args = f.read()
        proc = os.popen(runExec + " inputs/task" + str(n) + "_" + str(t) + ".pgm " + 
                        str(n) + " " + args)
        result = proc.read().strip()
        proc.close()

        expectedResult = open("outputs/task" + str(n) + "_" + str(t) + ".ref").read().strip()

        if expectedResult == result:
            result = "passed"
            pointsScored += pointsPerTask[t]
        else:
            result = "failed"

        start = "Task " + str(n) + " - Test " + str(t)
        print(start + "." * (len(header) - len(result) - len(start)) + result)

start = "README"
result = "failed"
if os.path.exists("./README"):
    result = "passed"
    pointsScored += 10

print(start + "." * (len(header) - len(result) - len(start)) + result)
totalScore = "Result: " + str(pointsScored) + "/100"
print("\n" + " " * (len(header) - len(totalScore)) + totalScore)

