#!/bin/bash

make
./tema1

score=0

begin_test=''
begin_result='reference/result_'
termination='.out'

arr=( "test0" "test1" "test2" "test3" "test4")
scores=( 10 10 15 25 25 )

for i in {0..4}
do
    element=${arr[$i]}
    testFileName=$begin_test$element$termination
    resultFileName=$begin_result$element$termination
    result=$(diff $testFileName $resultFileName | wc -l)

    if [ -f $testFileName ] && [ -f $resultFileName ] && [ "$result" -eq "0" ]; then
        echo "Test ${arr[$i]}...........................passed"
        score=$((score+${scores[$i]}))
    else
        echo "Test ${arr[$i]}...........................failed"
    fi
done

echo "                                      Total: $score"

make clean
