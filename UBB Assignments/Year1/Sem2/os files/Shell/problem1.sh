#!bin/bash

counter=0

for file in $(find $1); do
	if echo  $file | grep -q ".c$"
	then
		counter=$((counter+1))
	fi
done
echo $counter

