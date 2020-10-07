#!/bin/bash

num_points=90
num_tests=18
points_per_test=$((num_points/num_tests))
EXE=tema1
TESTING=checker
TOTAL=0

if [ ! -f 'README' ] && [ ! -f 'Readme' ] \
    && [ ! -f 'README.md' ] && [ ! -f 'Readme.md' ] \
    && [ ! -f 'README.txt' ] && [ ! -f 'Readme.txt' ]; then
    echo "README file not found!"
fi

make clean &>/dev/null
if [ $? -ne 0 ]; then
    echo "clean rule not found!"
    # exit 1
fi

make build &>/dev/null
if [ $? -ne 0 ]; then
    echo "build rule failed!"
    exit 1
fi

function check_task() {
    # @params: TASK_ID
    INPUT=in
    OUTPUT=out
    REF=ref

    if [ ! -f $1 ]; then
        echo "Executable file $1 was not generated!"
        exit 1
    fi

    echo

    for i in $(ls -v $INPUT); do
        IN_FILE=$INPUT/$i
        OUT_FILE=$OUTPUT/$(basename $i .in).out
        REF_FILE=$REF/$(basename $i .in).ref
        TEST_NR=$(echo $i | sed "s/test//" | sed "s/.in//")

        ./$1 < $IN_FILE > $OUT_FILE

        # diff will ignore all white spaces when comparing lines
        diff -Bbw $OUT_FILE $REF_FILE &> /dev/null
        if [ $? -eq 0 ]; then
            TOTAL=$((TOTAL + points_per_test))
            echo -e "Test $TEST_NR: passed ........................ "$points_per_test"/90"
        else
            echo -e "Test $TEST_NR: failed ........................ 0/90"
        fi
        # exit
    done
}


echo -e "\n================== TetriBit =================="

mkdir -p out

check_task $EXE

echo -e "\n=============================================="
echo "TOTAL: "$TOTAL"/90"
if [ $TOTAL -eq 90 ]; then
    echo "Congrats!"
fi
echo "=============================================="


echo -e "\nRemember: For the remaining 10% of the grade you need to include"
echo -e "\tan informative Readme file and and have a consistent coding style."

# rm -rf out
