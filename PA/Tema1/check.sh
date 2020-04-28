#!/bin/bash

# Darius-Florentin Neatu <neatudarius@gmail.com>
# Copyright 2018

DEBUG=on

total=0						# don't change
MAX_POINTS=150      		# you can change it
UTILS=_utils				# don't change
SOURCE_TMP_DIR=src_check	# don't change

# Put your tasks in this function
test_homework() {
	if [[ "$1" = "1" || "$1" = "teme" ]]; then
		test_teme
	elif [[ "$1" = "2" || "$2" = "magic" ]]; then
		test_magic
	elif [[ "$1" = "3" || "$3" = "ratisoare" ]]; then
		test_ratisoare
	elif [[ "$1" = "4" || "$4" = "joc" ]]; then
		test_joc
	elif [[ "$1" = "cs" ]]; then
		echo "skip running tests"
	else
		test_teme
		test_magic
		test_ratisoare
		test_joc
	fi
}


# Task 1
test_teme() {
	n_tests=30
	src_names=(teme.c teme.cpp teme.java)
	tests=( $(seq 0 $(($n_tests - 1))) )
	points=( $(printf '1.6 %.0s' $(seq 0 $(($n_tests - 1)))) )
	points[28]=2.2
	points[29]=3
	pmax=50

	run_problem teme 1
}

# Task 2
test_magic() {
	n_tests=40
	src_names=(magic.c magic.cpp magic.java)
	tests=( $(seq 0 $(($n_tests - 1))) )
	points=( $(printf '0.6 %.0s' $(seq 0 $(($n_tests - 1)))) )
	points[39]=1.6
	pmax=25

	run_problem magic 2
}

# Task 3
test_ratisoare() {
	n_tests=50
	src_names=(ratisoare.c ratisoare.cpp ratisoare.java)
	tests=( $(seq 0 $(($n_tests - 1))) )
	points=( $(printf '0.5 %.0s' $(seq 0 $(($n_tests - 1)))) )
	pmax=25

	run_problem ratisoare 3
}

# Task 4
test_joc() {
	n_tests=40
	src_names=(joc.c joc.cpp joc.java)
	tests=( $(seq 0 $(($n_tests - 1))) )
	points=( $(printf '1.25 %.0s' $(seq 0 $(($n_tests - 1)))) )
	points[38]=2.2
	points[39]=2.2
	pmax=50

	run_problem joc 4
}

###############################################################################
###############################################################################
###############################################################################
###############################################################################
###############################################################################
###############################################################################
###############################################################################
###############################################################################
###############################################################################
###############################################################################
###############################################################################

check_readme() {
	README=README

	echo "------------------------------------------------------------"
	echo "------------------------------------------------------------"
	echo "================>>>>>> Check $README <<<<<< ================"

	score=0
	max_score=0

	if (( $(echo "$total == 0" | bc -l)  )); then
		echo "Punctaj $README neacordat. Punctajul pe teste este $total!"
	elif [ ! -f $README ]; then
		score=-10
		echo "$README lipsa."
	elif [ -f $README ] && [ "`ls -l $README | awk '{print $5}'`" == "0" ]; then
		score=-10
		echo "$README gol."
	else
		score=$max_score
		echo "$README OK. Punctajul final se va acorda la corectare."
	fi

	total=$(bc <<< "$total + $score")

	echo "===============>>>>>> $README: $score/$max_score <<<<<< ==============="
	echo "-------------------------------------------------------------"
	echo "-------------------------------------------------------------"
}

check_cpp_errors() {
	cnt_cpp=$(cat $1 | grep "Total errors found" | cut -d ':' -f2 | cut -d ' ' -f2)
}

check_java_errors() {
	cnt_java=$(cat $1 | grep -E "(WARN)|(ERR)" | wc -l)
}

check_coding_style_full() {
	echo "-------------------------------------------------------------"
	echo "-------------------------------------------------------------"
	echo "===============>>>>>> Check coding style <<<<<< ==============="

	max_score=0
	score=$max_score

	if (( $(echo "$total == 0" | bc -l) )); then
		score=-5
		echo "Punctaj Coding style neacordat. Punctajul pe teste este $total!"
	else
		cpp_sources=$(find -L . -name '*.cpp' -o -name '*.c' -o -name '*.h' -o -name '*.hpp')
		java_sources=$(find -L . -name '*.java')

		if [ ! -z "${cpp_sources}" ]; then
			check_cpp=$UTILS/coding_style/check_cpp.py

			${check_cpp} ${cpp_sources} &>cpp.errors
			check_cpp_errors cpp.errors
		else
			echo "" > cpp.errors
			cnt_cpp=0
		fi

		if [ ! -z "${java_sources}" ]; then
			check_java=$UTILS/coding_style/check_java.jar
			java_errors=$UTILS/coding_style/java_errors.xml

			java -jar ${check_java} -c ${java_errors} ${java_sources} &>java.errors
			check_java_errors java.errors
		else
			echo "" > java.errors
			cnt_java=0
		fi

		if [ -z $ONLINE_JUDGE ]; then
			cat cpp.errors
			cat java.errors
		fi

		if (( ${cnt_cpp} > 0 || ${cnt_java} > 0 )); then
			score=-5

			echo "$cnt_cpp C/C++ errors found."
			echo "$cnt_java Java errors found."
		else
			echo "Coding style OK. Punctajul final se poate modifica la corectare."
		fi
	fi

	total=$(bc <<< "$total + $score")

	echo "===============>>>>>> Coding style: $score/$max_score <<<<<< ==============="
	echo "-------------------------------------------------------------"
	echo "-------------------------------------------------------------"
}


check_coding_style() {
	# Check if platform is online
	if [ -z $ONLINE_JUDGE ]; then
		check_coding_style_full
	else
		check_coding_style_dummy
	fi
}

timeout_test() {
	tag=$1
	timeout=$2

	(time timeout $timeout make $tag) &> error

	cnt=`cat error | grep "'$tag' failed" | wc -l`

	if [ $cnt -gt 0 ]; then
		t=`cat error | grep "real" | cut -d 'm' -f2 | cut -d 's' -f1 | tr ',' '.'`
		if [  $(echo "$t > $timeout" | bc) -eq 1  ]; then
			rm -f error
			echo "$t s" > tle
		fi
	else
		t=`cat error | grep "real" | cut -d 'm' -f2 | cut -d 's' -f1`
		echo "$t s" > output.time
		rm -f error
	fi
}

run_problem() {
	name=$1
	id=$2

	echo "------------------------------------------------------------"
	echo "------------------------------------------------------------"
	echo "---------------------- Problema $id: $name -----------------"

	score=0

	if  [ `find -L . -name ${src_names[0]} -o -name ${src_names[1]} -o -name ${src_names[2]} | wc -l` -gt 1  ]; then
		echo "Surse multiple pentru problema $name! Trimite doar una!"
		echo "Numele sursei care contine functia main trebuie sa fie:"
		echo "${src_names[0]}, ${src_names[1]} sau ${src_names[2]}"
		echo "=============>>>>>> Scor : $score/$pmax <<<<<< ============="
		echo "------------------------------------------------------------"
		echo "------------------------------------------------------------"
		return
	elif [ `find -L . -name ${src_names[0]} | wc -l` -eq 1  ]; then
		timeout=`cat $UTILS/timeout/c.timeout$id`
		echo "---------------------- timp C => $timeout s -----------------"
	elif [ `find -L . -name ${src_names[1]} | wc -l` -eq 1  ]; then
		timeout=`cat $UTILS/timeout/c.timeout$id`
		echo "---------------------- timp C++ => $timeout s -----------------"
	elif [ `find -L . -name ${src_names[2]} | wc -l` -eq 1  ]; then
		timeout=`cat $UTILS/timeout/java.timeout$id`
		echo "---------------------- timp Java => $timeout s -----------------"
	else
		echo "Numele sursei care contine functia main trebuie sa fie:"
		echo "${src_names[0]}, ${src_names[1]} sau ${src_names[2]}"
		echo "=============>>>>>> Scor : $score/$pmax <<<<<< ============="
		echo "------------------------------------------------------------"
		echo "------------------------------------------------------------"
		return
	fi

	if [ -z "`cat Makefile | grep run-p$id`" ]; then
		echo "Makefile: run-p${id} - regula make inexistenta!"
		echo "=============>>>>>> Scor : $score/$pmax <<<<<< ============="
		echo "------------------------------------------------------------"
		echo "------------------------------------------------------------"
		return
	fi

	rm -rf $TESTS_DIR/$name/out/
	mkdir -p $TESTS_DIR/$name/out/

	for i in "${tests[@]}"; do
		IN=$TESTS_DIR/$name/input/test$i.in
		REF=$TESTS_DIR/$name/ref/test$i.ref
		OUT=$TESTS_DIR/$name/out/test$i.out

		if [ $i -lt 10 ]
		then
			i=" "$i
		fi

		if [ ! -f $IN ]; then
			echo "Test $i problema $id .......... 0/${points[$i]} - $IN lipseste!"
			continue
		fi

		cp $IN $name.in
		cp $REF res.ok

		touch $name.out
		chmod 666 $name.out

		timeout_test run-p$id $timeout

		if [ -f error ]; then
			echo "Test $i problema $id .......... 0.0/${points[$i]} - Run time error!"
			# TODO
			# cat error
		elif [ -f tle ]; then
			echo "Test $i problema $id .......... 0.0/${points[$i]} - TLE - $(cat tle)!"
		else
			./verif $name ${points[$i]}

			STATUS=$(cat output.verif)
			TIME=$(cat output.time)
			SCORE=$(cat score.verif)
			echo "Test $i problema $id .......... $SCORE/${points[$i]} - $STATUS - $TIME"
			total=$(bc <<< "$total + $SCORE")
			score=$(bc <<< "$score + $SCORE")
		fi

		if [ ! -z $DEBUG ]; then
			cp $name.out  $OUT
		fi

		rm -f $name.in $name.out res.ok score.verif output.verif output.time \
		  error.time error.exec error expected.time tle time.err run.err sd run.out
	done

	if [[ "${name}" = "sala" ]]; then
		echo ""
		echo ""
		cat _utils/.suprise/yoda.ascii
		echo ""
		echo ""
		if (( $(echo "$score == $pmax" | bc -l) )); then
			if [ -z "$ONLINE_JUDGE" ]; then
				if [ $(which mpg123 2>&1 | wc -l) -eq 0 ]; then
					echo "'mpg123' must you install. Checker again must run. Bonus points may you lose!"
					echo "		e.g. sudo apt-get install mpg123"
					echo "		e.g. ./check.sh"
				else
					mpg123 _utils/.suprise/yoda.mp3 &>/dev/null
				fi
			fi
		fi
	fi

	echo "=============>>>>>> Scor : $score/$pmax <<<<<< ============="
	echo "------------------------------------------------------------"
	echo "------------------------------------------------------------"
}

if [[ "$1" = "h" || "$1" = "help" ]]; then
	echo "Usage:"
	echo "       ./check.sh                 # run the entire homework"
	echo "       ./check.sh task_id         # run only one problem (e.g. number or name)"
	echo "       ./check.sh cs              # run only the coding style check"
	exit 0
fi

TESTS_DIR=public_tests
if [ ! -z $1 ]; then
	# Check if platform is online
	ONLINE_JUDGE=
	if [ $1 = "ONLINE_JUDGE" ]; then
	 	ONLINE_JUDGE="ONLINE_JUDGE=\"-D=ONLINE_JUDGE\""
		TESTS_DIR=private_tests
	else
		TEST_TO_RUN=$1
	fi
else
	TEST_TO_RUN="ALL"
fi

# Check if Makefile exists
if [ ! -f Makefile ]; then
	echo "Makefile lipsa. STOP"
	echo "=============>>>>>> Total: $total/$MAX_POINTS <<<<<< ============="
	exit
fi

# Compile and check errors
make -f Makefile build &> out.make
cnt=$(cat out.make| grep failed | wc -l)

(g++ --version 2> /dev/null > tmp && cat tmp | head -1)  || (echo "Please install 'g++' :p!" && exit 1)
(gcc --version 2> /dev/null > tmp && cat tmp | head -1)  || (echo "Please install 'gcc' :p!" && exit 1)
javac -version											 || (echo "[Warning] Please install 'javac' if you're using Java :p." && exit 1)
python2.7 --version 									 || (echo "Please install 'python2.7' :p!'" && exit 1)
python3 --version	     								 || (echo "Please install 'python3' :p!" && exit 1)
rm -f tmp

# cat out.make
rm -f out.make
if [ $cnt -gt 0 ]; then
	echo "Erori de compilare. Verifica versiunea compilatorului. STOP"
	echo "=============>>>>>> Total: $total/$MAX_POINTS <<<<<< ============="
	exit
fi

# Compile checker
make -f Makefile.PA all $ONLINE_JUDGE &> /dev/null
rm -rf $SOURCE_TMP_DIR

# Display tests set
echo "---------------------- Run $TESTS_DIR -------------------"

# Run tests - change functions test_*
test_homework $TEST_TO_RUN
check_readme
check_coding_style_full

# Clean junk
make -f Makefile clean &> /dev/null
make -f Makefile.PA clean &> /dev/null
rm -rf tmp

# Display result
echo "Erorile de coding style se gasesc in cpp.errors / java.errors"
echo "=============>>>>>> Total: $total/$MAX_POINTS <<<<<< ============="

# Play bonus sound
if (( $(echo "$total == $MAX_POINTS" | bc -l) )); then
	if [ -z "$ONLINE_JUDGE" ]; then
		if [ $(which mpg123 2>&1 | wc -l) -eq 0 ]; then
			echo "'mpg123' must you install. Checker again must run. Bonus points may you lose!"
			echo "			e.g. sudo apt-get install mpg123"
			echo "			e.g. ./check.sh"
			exit 0
		fi
	fi

	echo ""
	echo "			PROUD OF YOU I AM!"
	echo ""

	if [ -z "$ONLINE_JUDGE" ]; then
		mpg123 _utils/.suprise/champions.mp3 &>/dev/null
	fi
fi
