#!/bin/bash

echo "Start time: $(date)"

FOLDERS=../tests/*
HW_PATH=com/apd/tema2/Main
ROOT=./src
ERR=./err
OUT=./out

echo -e "Show CPU info (lscpu)\n\n"
lscpu

echo -e "\n\nShow memory info (free -m)\n\n"
free -m
echo -e "\n\n"

echo -e "Unzip tests and student solution\n\n"

unzip artifact.zip
unzip archive.zip

echo -e "\n\nRunning the checker\n\n"

if [ -d "$ROOT" ]; then
	rm -rf out err src/bin
	mkdir out err
	cd src

	javac -g $HW_PATH.java -d bin

	for d in $FOLDERS
	do	
		for f in $d/*
		do
    			echo "Processing $f file..."
    		
			fullpath=`echo "${f%.*}"`
			filename="${fullpath##*/}"

			timeout 180 java -cp bin/ $HW_PATH $f > ../out/$filename.out
			
			x=0

			while [ $x -le 4 ] && [[ $filename =~ ^complex_maintenance_[0-9]$ ]] && [ ! -s ../out/$filename.out ]
			do
				timeout 180 java -cp bin/ $HW_PATH $f > ../out/$filename.out
				x=$(( $x + 1))

				if [ -s ../out/$filename.out ]
				then
					echo $filename filled after $x attempts
				fi
			done

			if [ ! -s ../out/$filename.out ]
                        then
                                echo $filename filled after $x attempts
			fi

			if [ $? != 0 ]
			then
				echo "Timer exceeded"
			fi
		done
	done

	cd ..
	timeout 180 java -jar ./Tema2Checker_J8.jar

	for f in $ERR/*
        do
               	if [[ -s $f ]]
		then
			echo "Contents of the err file $f"
			cat $f

			fullpath=`echo "${f%.*}"`
                        filename="${fullpath##*/}"

			echo "Contents of the out file $filename.out"
			head --lines=150 $OUT/$filename.out
		fi
	done

	
else
	echo "src not found"
fi

echo "End time: $(date)"
