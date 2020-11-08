#!/bin/bash

correct=0
total=0
scalability=0
correctness=0
correct_scalability=2
times=()
seq_times=()
par_times=()
seq_runs=0

# afiseaza scorul final
function show_score {
	echo ""
	echo "Scor scalabilitate: $scalability/50"
	echo "Scor corectitudine: $correctness/30"
	echo "Scor total:         $((correctness + scalability))/80"
}

# se compara doua fisiere (parametri: fisier1 fisier2 test_scalabitate)
function compare_outputs {
	diff -q $1 $2 &> /dev/null
	if [ $? == 0 ]
	then
		correct=$((correct+1))
	else
		echo "W: Exista diferente intre fisierele $1 si $2"

		if [ $3 == 1 ]
		then
			correct_scalability=$((correct_scalability-1))
		fi
	fi
}

# se ruleaza o comanda si se masoara timpul (parametru: comanda)
function run_and_get_time_seq {
	{ time -p sh -c "$1"; } &> time.txt
	ret=$?

	if [ $ret != 0 ]
	then
		echo "E: Rularea nu s-a putut executa cu succes"
		cat time.txt | sed '$d' | sed '$d' | sed '$d'
		show_score
		exit
	fi

	res=`cat time.txt | grep real | awk '{print $2}'`
	seq_times+=(${res})
	times+=(${res%.*})

	rm -rf time.txt

	seq_runs=$((seq_runs+1))
}

# se ruleaza o comanda paralela (parametri: timeout comanda)
function run_par {
	{ timeout $1 $2; } &> out.txt
	ret=$?

	if [ $ret == 124 ]
	then
		echo "W: Programul a durat cu cel putin 3 secunde in plus fata de implementarea secventiala"
	elif [ $ret != 0 ]
	then
		echo "W: Rularea nu s-a putut executa cu succes"
		cat out.txt
	fi

	rm -rf out.txt

	total=$((total+2))
}

# se ruleaza si masoara o comanda paralela (parametri: timeout comanda)
function run_par_and_measure {
	{ time -p sh -c "timeout $1 $2" ; } &> time.txt
	ret=$?

	if [ $ret == 124 ]
	then
		echo "W: Programul a durat cu cel putin 3 secunde in plus fata de implementarea secventiala"
	elif [ $ret != 0 ]
	then
		echo "W: Rularea nu s-a putut executa cu succes"
		cat time.txt | sed '$d' | sed '$d' | sed '$d'
	fi

	total=$((total+2))
	par_times+=(`cat time.txt | grep real | awk '{print $2}'`)
	rm -rf time.txt
}

# se compileaza cele doua implementari (cea paralela si cea secventiala)
cd ../skel
make clean &> /dev/null
make build &> /dev/null

if [ ! -f tema1 ]
then
    echo "E: Nu s-a putut compila implementarea secventiala"
    show_score
    cd ../sol
    exit
fi

cd ../sol
make clean &> /dev/null
make build &> /dev/null

if [ ! -f tema1_par ]
then
    echo "E: Nu s-a putut compila implementarea paralela"
    show_score
    exit
fi

# se ruleaza cele 4 teste pe varianta secventiala
echo "Se ruleaza implementarea secventiala..."
run_and_get_time_seq "../skel/tema1 tests/julia1.in julia1_sec.pgm tests/mandelbrot1.in mandelbrot1_sec.pgm"
run_and_get_time_seq "../skel/tema1 tests/julia2.in julia2_sec.pgm tests/mandelbrot2.in mandelbrot2_sec.pgm"
run_and_get_time_seq "../skel/tema1 tests/julia3.in julia3_sec.pgm tests/mandelbrot3.in mandelbrot3_sec.pgm"
run_and_get_time_seq "../skel/tema1 tests/julia4.in julia4_sec.pgm tests/mandelbrot4.in mandelbrot4_sec.pgm"
echo "OK"
echo ""

# se cresc valorile de timeout cu cate 2 secunde pentru fiecare test
for (( i=0; i<$seq_runs; i++ ))
do
   times[$i]=$((times[$i]+2))
done

# se ruleaza implementarea paralela pe diferite combinatii de numar de thread-uri
for P in 2 3 4
do
	echo "Se ruleaza testele pentru P=$P..."
	
	# pentru primul test, se masoara timpii ptr P=2 si P=4 (pentru calculul acceleratiei)
	if [ "$P" == "2" ] || [ "$P" == "4" ]
	then
		run_par_and_measure ${times[0]} "./tema1_par tests/julia1.in julia1_par.pgm tests/mandelbrot1.in mandelbrot1_par.pgm $P"
	else
		run_par ${times[0]} "./tema1_par tests/julia1.in julia1_par.pgm tests/mandelbrot1.in mandelbrot1_par.pgm $P"
	fi

	run_par ${times[1]} "./tema1_par tests/julia2.in julia2_par.pgm tests/mandelbrot2.in mandelbrot2_par.pgm $P"
	run_par ${times[2]} "./tema1_par tests/julia3.in julia3_par.pgm tests/mandelbrot3.in mandelbrot3_par.pgm $P"
	run_par ${times[3]} "./tema1_par tests/julia4.in julia4_par.pgm tests/mandelbrot4.in mandelbrot4_par.pgm $P"

	# pentru primul test, se tine minte daca rezultatul e corect pentru P=2 si P=4 (pentru punctajul de scalabilitate)
	if [ "$P" == "2" ] || [ "$P" == "4" ]
	then
		compare_outputs julia1_sec.pgm julia1_par.pgm 1
		compare_outputs mandelbrot1_sec.pgm mandelbrot1_par.pgm 1
	else
		compare_outputs julia1_sec.pgm julia1_par.pgm 0
		compare_outputs mandelbrot1_sec.pgm mandelbrot1_par.pgm 0
	fi

	compare_outputs julia2_sec.pgm julia2_par.pgm 0
	compare_outputs mandelbrot2_sec.pgm mandelbrot2_par.pgm 0

	compare_outputs julia3_sec.pgm julia3_par.pgm 0
	compare_outputs mandelbrot3_sec.pgm mandelbrot3_par.pgm 0

	compare_outputs julia4_sec.pgm julia4_par.pgm 0
	compare_outputs mandelbrot4_sec.pgm mandelbrot4_par.pgm 0

	rm -rf julia*_par.pgm
	rm -rf mandelbrot*_par.pgm

	echo "OK"
	echo ""
done

echo "Teste corecte: $correct/$total"

# se calculeaza acceleratia (este folosit primul test)
speedup12=$(echo "${seq_times[0]}/${par_times[0]}" | bc -l)
speedup14=$(echo "${seq_times[0]}/${par_times[1]}" | bc -l)
speedup24=$(echo "${par_times[0]}/${par_times[1]}" | bc -l)

# acceleratia se considera 0 daca testele de scalabilitate nu sunt corecte
if [ $correct_scalability != 2 ]
then
	speedup12=0
	speedup14=0
	speedup24=0
fi

printf "Acceleratie 1-2: %0.2f\n" $speedup12
printf "Acceleratie 1-4: %0.2f\n" $speedup14
printf "Acceleratie 2-4: %0.2f\n" $speedup24

# se verifica acceleratia de la secvential la 2 thread-uri
max=$(echo "${speedup12} > 1.25" | bc -l)
part=$(echo "${speedup12} > 1.1" | bc -l)
if [ $max == 1 ]
then
	scalability=$((scalability+20))
elif [ $part == 1 ]
then
	scalability=$((scalability+10))
	echo "W: Acceleratia de la 1 la 2 thread-uri este prea mica (punctaj partial)"
else
    echo "W: Acceleratia de la 1 la 2 thread-uri este prea mica (fara punctaj)"
fi

# se verifica acceleratia de la secvential la 4 thread-uri
max=$(echo "${speedup14} > 2.3" | bc -l)
part=$(echo "${speedup14} > 1.7" | bc -l)
if [ $max == 1 ]
then
	scalability=$((scalability+20))
elif [ $part == 1 ]
then
	scalability=$((scalability+10))
	echo "W: Acceleratia de la 1 la 4 thread-uri este prea mica (punctaj partial)"
else
    echo "W: Acceleratia de la 1 la 4 thread-uri este prea mica (fara punctaj)"
fi

# se verifica acceleratia de la 2 la 4 thread-uri
max=$(echo "${speedup24} > 1.2" | bc -l)
if [ $max == 1 ]
then
	scalability=$((scalability+10))
else
    echo "W: Acceleratia de la 2 la 4 thread-uri este prea mica (fara punctaj)"
fi

rm -rf julia*_sec.pgm
rm -rf mandelbrot*_sec.pgm

cd ../skel
make clean &> /dev/null

cd ../sol
make clean &> /dev/null

if [ $scalability != 0 ]
then
	correctness=$((correct * 30 / total))
fi

show_score
