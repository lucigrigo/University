#!/bin/bash
# credits to AI CG :D

CHECKER_DIR=`dirname $0`/checker
TEST_SUITE=${@:-test bigtest extra bigextra error exception exceptionextra bonus bigbonus exceptionbonus}
TEST_DIR=$CHECKER_DIR/tests
LOG_DIR=${CHECKER_DIR}/logs
INPUT_FILE="code"

min() {
    awk -v n1="$1" -v n2="$2" 'BEGIN {printf "%s\n",(n1<n2?n1:n2)}'
}

max() {
    awk -v n1="$1" -v n2="$2" 'BEGIN {printf "%s\n",(n1<n2?n2:n1)}'
}

run_tests (){
    for suite in ${TEST_SUITE}
    do
        for src in `find ${TEST_DIR} -iname "${suite}[0-9]*.gly"`
        do
            test_name=`basename ${src/.gly/}`
            input=${src/.gly/.in}
            output=${src/.gly/.out}
            error=${src/.gly/.err}
            retval=`cat ${src/.gly/.ret}`

            OUTPUT_FILE=$test_name.rawout
            CLEARED_OUTPUT=$test_name.out
            ERROR_FILE=$test_name.rawerr
            CLEARED_ERROR=${test_name}.err

            if [ -f mytime.cfg ]
            then
                time_pref=`grep ^${test_name} mytime.cfg | cut -d ' ' -f 2`
            fi
            time=${time_pref:-${time_test}}
            time=`min ${time} ${TIME_LEFT}`

            unset base
            rm $INPUT_FILE $OUTPUT_FILE $ERROR_FILE $CLEARED_OUTPUT $CLEARED_ERROR &> /dev/null
            cp ${src} $INPUT_FILE

            if [[ $test_name =~ big.* ]]
            then
                weight=3
            else
                weight=1
            fi
            total_score=$[total_score + $weight]

            if [[ "$time" = "0" ]]
            then
                echo -e "Skipping \e[1;33m$test_name\e[0m."
                continue
            fi

            #echo "Time allowed $time"

            if [[ $test_name =~ .*bonus.* ]]
            then
                base=`grep ^${test_name} ${CHECKER_DIR}/base.cfg | cut -d ' ' -f 2`
            fi

            # Run the student homework
            #echo "Running: make -s run input=${src} base=$base < ${input} > $OUTPUT_FILE 2> $ERROR_FILE"
            START=$(date +%s.%N)
            timeout $time make -s run input=${INPUT_FILE}  base=$base < ${input} > $OUTPUT_FILE 2> $ERROR_FILE
            timeret=$?
            END=$(date +%s.%N)
            DIFF=$(echo "$END - $START" | bc)

            TIME_LEFT=$(max `echo "$TIME_LEFT - $DIFF" | bc` 0)

            if [ $timeret = 124 ]
            then
                echo -e "\e[31mFAILED\e[0m Test \e[1;33m$test_name\e[0m. You failed to win: $weight"
                echo "make -s run input=${src} base=$base < ${input} > $OUTPUT_FILE 2> $ERROR_FILE" > ${LOG_DIR}/$test_name.command
                echo "Timeout $DIFF/$time"
                rm ${OUTPUT_FILE} ${CLEARED_OUTPUT} ${CLEARED_ERROR} ${ERROR_FILE} 2>/dev/null
            else
                cat "$OUTPUT_FILE" | grep -vi Makefile > "$CLEARED_OUTPUT"
                diff -bBq "$CLEARED_OUTPUT" "${output}" &> /dev/null
                outcmp=$?

                make_error_line=`cat $ERROR_FILE | sed 's/make.* /\nmake: /' | grep ^make`
                RETVAL="${make_error_line##* }"
                RETVAL="${RETVAL:-0}"

                cat $ERROR_FILE | sed 's/make.* /\nmake: /' | grep -v ^make > ${CLEARED_ERROR}
                diff -bBq "$CLEARED_ERROR" "${error}" &> /dev/null
                errcmp=$?

                if [ "$outcmp" = "0" ] && [ "$errcmp" = "0" ] && [ "$RETVAL" = "$retval" ]
                then
                    echo -e "\e[32mPASSED\e[0m Test \e[1;33m$test_name\e[0m. You won: $weight"
                    rm ${OUTPUT_FILE} ${CLEARED_OUTPUT} ${CLEARED_ERROR} ${ERROR_FILE} 2>/dev/null
                    score=$[$score + $weight];
                else
                    echo -e "\e[31mFAILED\e[0m Test $\e[1;33m$test_name\e[0m. You failed to win: $weight"
                    mv ${OUTPUT_FILE} ${CLEARED_OUTPUT} ${CLEARED_ERROR} ${ERROR_FILE} ${LOG_DIR}
                    echo ${RETVAL} > ${LOG_DIR}/${test_name}.ret
                    echo "make -s run input=${src} base=$base < ${input} > $OUTPUT_FILE 2> $ERROR_FILE" > ${LOG_DIR}/$test_name.command
                    echo " failed outputs saved in ${LOG_DIR}"
                    echo "Output comparison: ${outcmp}, expected 0"
                    echo "Error comparison: ${errcmp}, expected 0"
                    echo "Return value comparison: ${RETVAL}, expected ${retval}"
                fi
            fi

            echo "Time left ${TIME_LEFT}"
        done
    done
}


# Compile student homework
make build
mkdir -p ${LOG_DIR}
rm ${LOG_DIR}/* 2>/dev/null

# if missing, generate tests
echo "Generating tests"
python3 $CHECKER_DIR/glypher.py ${TEST_DIR}/*.gsh > /dev/null

echo "Starting"

# Run tests
score=0
total_score=0

if [[ `make run -n input=x base=x` =~ .*python.* ]]
then
    TIME_LEFT="300"
    time_test="1.5"
else
    TIME_LEFT="150"
    time_test="0.75"
fi

run_tests

rm $INPUT_FILE &> /dev/null
#make clean

echo "Score: $score out of $total_score"
