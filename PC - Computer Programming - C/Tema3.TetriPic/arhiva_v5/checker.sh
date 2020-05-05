#!/bin/bash


function init {

    numberOfTests=100

    total_per_task[1]=0
    total_per_task[2]=0
    total_per_task[3]=0
    total_per_task[4]=0

    total_score=0
    pad=$(printf '%.1s' "."{1..70})
    padlength=71

    make build
    if [ $? -ne 0 ]; then
        echo "Makefile failed!"
        exit 1
    fi
}

function print_result {
    printf "%s" "$1"
    printf "%*.*s" 0 $((padlength - ${#1} - ${#2} )) "$pad"
    printf "%s\n" "$2"
}


function check_task1 {
	blocks=("O" "I" "S" "Z" "L" "J" "T")
	current_test=1

	echo "..............................TASK 1..................................."
	make run_task1 &> /dev/null
    if [ $? -ne 0 ]; then
        echo "Makfile run_task1 failed!"
        return
    fi

	for i in "${blocks[@]}"
	do
		ref_file="ref_$i.bmp"
		output_file="piesa_$i.bmp"

		cp "ref/task1/$ref_file" "$ref_file" &> /dev/null

		if [ -f $output_file ]; then
			diff -w $output_file $ref_file &> /dev/null

			if [ $? -eq 0 ]; then
				let "total_score += 4"
                print_result "Test $current_test for block $i" "passed"
			else
                print_result "Test $current_test for block $i" "failed"
			fi

			rm "$output_file"
		else
                print_result "Test $current_test for block $i" "missing file"
		fi

		let "current_test += 1"
		rm "$ref_file"
	done
}

function check_task2 {
	blocks=("O" "I" "S" "Z" "L" "J" "T")
	degrees=("90" "180" "270")
	current_test=7

	echo "..............................TASK 2..................................."
	make run_task2 &> /dev/null
    if [ $? -ne 0 ]; then
        echo "Makfile run_task2 failed!"
        return
    fi

	for i in "${blocks[@]}"
	do
		total_block=0
		missing_file=0

		for j in "${degrees[@]}"
		do
			ref_file="ref_${i}_${j}.bmp"
			output_file="piesa_${i}_${j}.bmp"

			cp "ref/task2/$ref_file" "$ref_file" &> /dev/null

			if [ -f $output_file ]; then
				diff -w $output_file $ref_file &> /dev/null

				if [ $? -eq 0 ]; then
					let "total_block += 1"
				fi

			    rm "$output_file"
			else
				let "missing_file += 1"
			fi

			rm "$ref_file"
		done

		let "current_test += 1"

		if [ $missing_file -eq 3 ]; then
                print_result "Test $current_test for block $i" "missing files"
		else
			if [ $total_block -eq 3 ]; then
                print_result "Test $current_test for block $i" "passed"
			else
                print_result "Test $current_test for block $i" "failed"
			fi
		fi

        let "total_score += (2 * total_block)"
	done
}

# 15 de teste
function check_task3 {
	current_test=15

	echo "..............................TASK 3..................................."
	for i in `seq 0 14`
	do
        ref_file="ref_$i.bmp"
		input_file="input_$i.in"
		output_file="task3.bmp"

		cp "ref/task3/$ref_file" "$ref_file" &> /dev/null
		cp "input/task3/$input_file" "cerinta3.in" &> /dev/null

    	make run_task3 &> /dev/null
        if [ $? -ne 0 ]; then
            echo "Makfile run_task3 failed!"
            return
        fi

		if [ -f $output_file ]; then
			diff -w $output_file "$ref_file" &> /dev/null

			if [ $? -eq 0 ]; then
				let "total_score += 2"
                print_result "Test $current_test" "passed"
			else
                print_result "Test $current_test" "failed"
			fi

			rm "$output_file"
		else
                print_result "Test $current_test" "missing file"
		fi

		let "current_test += 1"
		rm "$ref_file"
		rm "cerinta3.in"
	done
}

#10 teste
function check_task4 {
	current_test=30
	output_file="task4.bmp"

	echo "..............................TASK 4..................................."
	for i in `seq 0 9`
	do
		ref_file="ref_$i.bmp"
		bmp_file="input_$i.bmp"
		input_file="input_$i.in"

		cp "ref/task4/$ref_file" "$ref_file" &> /dev/null
		cp "input/task4/$input_file" "cerinta4.in" &> /dev/null
		cp "input/task4/$bmp_file" "cerinta4.bmp" &> /dev/null

        make run_task4 &> /dev/null
        if [ $? -ne 0 ]; then
            echo "Makfile run_task4 failed!"
            return
        fi

		if [ -f $output_file ]; then
			diff -w $output_file $ref_file &> /dev/null

			if [ $? -eq 0 ]; then
				let "total_score += 4"
				print_result "Test $current_test" "passed"
			else
				print_result "Test $current_test" "failed"
			fi

			rm "$output_file"
		else
                print_result "Test $current_test" "missing file"
		fi

		let "current_test += 1"
		rm "$ref_file"
		rm "cerinta4.in"
		rm "cerinta4.bmp"

	done
}

#5 teste
function check_bonus {
	current_test=40

	echo "...............................BONUS..................................."
	for i in `seq 0 4`
	do
		ref_file="ref_$i.out"
		bmp_file="input_$i.bmp"
		output_file="bonus.out"

		cp "ref/bonus/$ref_file" "$ref_file" &> /dev/null
		cp "input/bonus/$bmp_file" "bonus.bmp" &> /dev/null

        make run_bonus &> /dev/null
        if [ $? -ne 0 ]; then
            echo "Makfile run_bonus failed!"
            return
        fi

		if [ -f $output_file ]; then
            sort -o $output_file $output_file
            sort -o $ref_file $ref_file
            diff -w $output_file $ref_file &> /dev/null

			if [ $? -eq 0 ]; then
				let "total_score += 6"
                print_result "Test $current_test" "passed"
			else
                print_result "Test $current_test" "failed"
			fi

			rm "$output_file"
		else
                print_result "Test $current_test" "${total_score}/170"
		fi

		let "current_test += 1"
		rm "$ref_file"
		rm "bonus.bmp"
	done
}

init

check_task1
check_task2
check_task3
check_task4
check_bonus

print_result "Final score" "${total_score}/170"

if [ $total_score -eq 170 ]
then
    iterations=0
    trap "tput reset; tput cnorm; exit" 2
    clear
    tput civis
    lin=2
    col=$(($(tput cols) / 2))
    c=$((col-1))
    est=$((c-2))
    color=0
    tput setaf 2; tput bold

    # Tree
    for ((i=1; i<20; i+=2))
    {
        tput cup $lin $col
        for ((j=1; j<=i; j++))
        {
            echo -n \*
        }
        let lin++
        let col--
    }

    tput sgr0; tput setaf 3

    # Trunk
    for ((i=1; i<=2; i++))
    {
        tput cup $((lin++)) $c
        echo 'mWm'
    }
    new_year=$(date +'%Y')
    let new_year++
    tput setaf 1; tput bold
    tput cup $lin $((c - 6)); echo MERRY CHRISTMAS
    tput cup $((lin + 2)) $((c - 17)); echo YOU GOT A MAXIMUM SCORE ON THE HOMEWORK
    tput cup $((lin + 1)) $((c - 10)); echo And lots of CODE in $new_year
    let c++
    k=1

    # Lights and decorations
    while [ $iterations -lt 3 ]; do
        for ((i=1; i<=35; i++)) {
            # Turn off the lights
            [ $k -gt 1 ] && {
                tput setaf 2; tput bold
                tput cup ${line[$[k-1]$i]} ${column[$[k-1]$i]}; echo \*
                unset line[$[k-1]$i]; unset column[$[k-1]$i]  # Array cleanup
            }

            li=$((RANDOM % 9 + 3))
            start=$((c-li+2))
            co=$((RANDOM % (li-2) * 2 + 1 + start))
            tput setaf $color; tput bold   # Switch colors
            tput cup $li $co
            echo o
            line[$k$i]=$li
            column[$k$i]=$co
            color=$(((color+1)%8))

            # Flashing text
            sh=1
            for l in C O D E
            do
                tput cup $((lin+1)) $((c+sh))
                echo $l
                let sh++
                sleep 0.01
            done
        }

        k=$((k % 2 + 1))
        iterations=$((iterations+1))
    done
    clear
fi

make clean &> /dev/null
