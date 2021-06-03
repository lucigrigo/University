import traceback
import sys, os, subprocess, signal
from subprocess import STDOUT, check_output

programs = [
    'gpu_hashtable',
]

testConfig = [
    {
        "name" : "T1",
        "entries" : 10 ** 6,
        "chunks" : 1,
        "speed" : 10,
        "points" : 20
    },
    {
        "name" : "T2",
        "entries" : 10 ** 6,
        "chunks" : 2,
        "speed" : 20,
        "points" : 20
    },
    {
        "name" : "T3",
        "entries" : 10 ** 6,
        "chunks" : 8,
        "speed" : 40,
        "points" : 15
    },
    {
        "name" : "T4",
        "entries" : 10 ** 7,
        "chunks" : 4,
        "speed" : 50,
        "points" : 15
     },
    {
        "name" : "T5",
        "entries" : 4 * (10 ** 7),
        "chunks" : 2,
        "speed" : 50,
        "points" : 15
    },
]

outfile = open('output', 'w')

if len(sys.argv) > 1:
    benchtypes = sys.argv[1:]
else:
    benchtypes = ('0', '1')

for program in programs:

    programName = program
    hwMaxPoints = 0
    hwPoints = 0

    for testEntry in testConfig:

        testName = testEntry["name"]
        testEntries = str(testEntry["entries"])
        testChunks = str(testEntry["chunks"])
        testSpeed = str(testEntry["speed"])
        testPoints = testEntry["points"]
        hwMaxPoints += testPoints

        print( "\n\n\n------- Test %s START\t----------\n" % (testName) )

        try:
            output = subprocess.check_output(['./' + program, testEntries, testChunks, testSpeed])
            lines = str(output).split("\n")
            print( output )
 
        except Exception:

            print( "------- Test %s END\t---------- \t [ FAILED ]" % (testName) )
            traceback.print_exc()
            print( "Error with %s" % str(['./' + program, testEntries, testChunks, testSpeed]))
            continue

        print( "------- Test %s END\t---------- \t [ OK RESULT: +%d pts ]" % (testName, testPoints) )
        hwPoints = hwPoints + testPoints


    print( "\nTOTAL %s  %d/%d" % (program, hwPoints, hwMaxPoints) )
        
