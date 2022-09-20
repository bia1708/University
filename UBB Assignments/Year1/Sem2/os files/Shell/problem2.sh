#!bin/bash

word=$1
notimes=$2
line=$3
shift 3

for file in $@; do
	linecounter=1
	wordcounter=0
	while read fileline; do
		if [ $linecounter -eq $line ]
		then 
			for fileword in $fileline; do
				if [ $word = $fileword ]
				then
					wordcounter=$((wordcounter+1))
				fi
		done
		fi
		linecounter=$((linecounter+1))
	done<$file

	if [ $wordcounter -eq $notimes ]
	then
		echo $file
	fi
	shift 1
done

