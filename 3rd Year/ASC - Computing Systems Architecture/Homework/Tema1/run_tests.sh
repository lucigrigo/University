#!/bin/bash

SRC=tema
TESTS=tests
OUT=out
PYTHON_CMD=python3

for i in {1..8}
do
    TIMEOUT_VALS[$i]=30
done
for i in {9..10}
do
    TIMEOUT_VALS[$i]=60
done

# Cleanup the previous run's temporary files
rm -f ${TESTS}/*.out.sorted

# Run tests
for i in {1..10}
do
    prefix=$(printf "%02d" $i)
    rm -f "${TESTS}/$prefix".out
    echo "Starting test $i"

    timeout ${TIMEOUT_VALS[i]} ${PYTHON_CMD} test.py "${TESTS}/$prefix.in" > "${TESTS}/$prefix.out"
    if [ ! $? -eq 0 ]
    then
        echo "TIMEOUT. Test $i exceeded maximum allowed time of ${TIMEOUT_VALS[i]}"
    fi

    echo "Finished test $i"
    ${PYTHON_CMD} check_test.py $i "${TESTS}/$prefix.out" "${TESTS}/$prefix.ref.out"
done

# Pylint checks - the pylintrc file being in the same directory
# Uncoment the following line to check your implementation's code style :)
# ${PYTHON_CMD} -m pylint ${SRC}/*.py
