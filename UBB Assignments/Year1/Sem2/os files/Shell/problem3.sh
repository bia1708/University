#!bin/bash

word=$1

shift 1

for file in $@; do
	counter=0
	for fileword in $(cat $file); do
		if [ $fileword = $word ]
		then
			counter=$((counter+1))
		fi
	done
	echo $file $counter
done
