#!/bin/bash

TOTAL=0
PROGRAM="./format_text"
TMP_OUTPUT_FILE="out.txt"
TMP_OUTPUT="output"
TIMEOUT_T=5
LOG="/dev/null"

PROBLEM_NAME=("wrap" "center" "align_left" "align_right" "justify" "paragraphs" "lists" "ordered_lists" "combined" "errors")
NUM_TESTS=(6 5 5 5 5 5 5 5 9 15)
SCORE=(30 5 5 5 30 5 10 20 45 15)
NUM_PROBLEMS=10
MAX_SCORE=170
MAX_SCORE_NO_BONUS=140

ERR_MSG=("Cannot wrap!"
         "Invalid operation!"
         "Invalid operation!"
         "Invalid operation!"
         "Invalid operation!"
         "Invalid operation!"
         "Invalid operation!"
         "Invalid operation!"
         "Invalid operation!"
         "Invalid operation!"
         "Invalid operation!"
         "Invalid operation!"
         "Invalid operation!"
         "Invalid operation!"
         "Too many operations! Only the first 10 will be applied.")

MESSAGE="msg"
touch $MESSAGE

make build &> $LOG

function print_header {
    echo "=================== Format text ==================="
    echo
}


function print_total {
    echo "==================================================="
    SCORE_MSG="TOTAL: $TOTAL/$MAX_SCORE"
    SPACE_COUNT=$(((50 - ${#SCORE_MSG}) / 2))
    printf ' %.0s' $(seq 1 $SPACE_COUNT)
    echo $SCORE_MSG
    if [ $TOTAL = $MAX_SCORE ]; then
    	echo
    	echo '        ,-.                     .       . '
		echo '       /                        |       | '
		echo '       |    ,-. ;-. ,-: ;-. ,-: |-  ,-. | '
		echo '       \    | | | | | | |   | | |   `-.   '
		echo '        `-'"'"' `-'"'"' '"'"' '"'"' `-| '"'"'   `-` `-'"'"' `-'"'"' o  '
		echo '                    `-'"'"'                   '
	elif [[ $TOTAL -ge $MAX_SCORE_NO_BONUS ]]; then
	    echo "                   Almost there!"
	fi
    echo "==================================================="
}

function print_pass {
    TEST_NR="$1"
    NAME=${PROBLEM_NAME[$2]}
    PROB_SCORE=${SCORE[$2]}
    TEST_SCORE=$((PROB_SCORE / NUM_TESTS[$2]))
    TEST_NAME="$NAME - test$1"
    DOT_COUNT=$((40 - ${#TEST_NAME}))

    printf "$TEST_NAME"
    printf '.%.0s' $(seq 1 $DOT_COUNT)
    echo "PASSED $TEST_SCORE/$PROB_SCORE"
    TOTAL=$((TOTAL + TEST_SCORE))
}


function print_failed {
    TEST_NR="$1"
    NAME=${PROBLEM_NAME[$2]}
    PROB_SCORE=${SCORE[$2]}
    TEST_NAME="$NAME - test$1"
    DOT_COUNT=$((40 - ${#TEST_NAME}))

    printf "$TEST_NAME"
    printf '.%.0s' $(seq 1 $DOT_COUNT)
    echo "FAILED 0/$PROB_SCORE"
}


function verify_test {
    TEST_NR="$1"
    NAME=${PROBLEM_NAME[$2]}
    TEST_INPUT_PATH="$NAME/$NAME$1.in"
    TEST_OUTPUT_PATH="$NAME/$NAME$1.ok"
    COMMAND=$(cat "$NAME/$NAME$1.cmd")

    timeout $TIMEOUT_T $PROGRAM "$COMMAND" $TEST_INPUT_PATH $TMP_OUTPUT_FILE > $TMP_OUTPUT
    ok=1

    if [ $NAME = "errors" ]; then
        echo ${ERR_MSG[$TEST_NR]} > $MESSAGE
    fi

    diff "$TMP_OUTPUT" "$MESSAGE" &> $LOG
    if [ $? -ne 0 ]; then
        ok=0
    fi

    if [ $NAME = "justify" ]; then
        justify/check "$COMMAND" $TMP_OUTPUT_FILE $TEST_INPUT_PATH &> $LOG
    else
        diff "$TEST_OUTPUT_PATH" "$TMP_OUTPUT_FILE" &> $LOG
    fi

    if [ $? -ne 0 ]; then
        ok=0
    fi

    if [ $ok -eq 1 ]; then
        print_pass "$TEST_NR" "$2"
    else
        print_failed "$TEST_NR" "$2"
    fi

    rm -f "$TMP_OUTPUT"
    rm -f "$TMP_OUTPUT_FILE"
}

if [ $# -ne 0 ]; then
    echo "Usage: bash checker.sh"
    exit 1
fi

print_header

for problem in $(seq 0 $((NUM_PROBLEMS - 1))); do
    for nr in $(seq 0 $((NUM_TESTS[$problem] - 1))); do
        verify_test "$nr" "$problem"
    done
    echo
done

print_total
rm -f "$INVALID_OPERATION" "$MESSAGE"

make clean &> $LOG
