#!bin/bash

number=$1
word=$2
shift 2

for file in $@; do
	counter=0
	while read line; do
		if echo $line | grep -qE "\<$word\>"; then
			counter=$((counter+1))
		fi
		if [ $counter -eq $number ]; then
			echo "$file: "
			echo $line
			break
		fi
	done<$file
done
