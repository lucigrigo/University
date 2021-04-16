#!/bin/bash

TIMEOUT_VAL=360
PYTHON_CMD=python3
SRC=tema

timeout $TIMEOUT_VAL ./run_tests.sh &> result

if [ ! $? -eq 0 ]
then
    echo "TIMEOUT. Tests exceeded maximum allowed time of $TIMEOUT_VAL" >> result
fi

echo -e "\nRun pylint\n" >> result
${PYTHON_CMD} -m pylint --rcfile=./pylintrc ${SRC}/*.py &>> result

awk -f parse.awk result

echo -e "\nDetailed report\n"
cat result
