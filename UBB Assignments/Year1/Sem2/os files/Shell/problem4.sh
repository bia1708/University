#!bin/bash

number=$1

shift 1

result=""

for file in $@; do
	echo "The libraries used in $file are:"
	cat $file | grep -E "^[#]include [<].{1,}[>]$" | sed -E 's/^[#]include [<](.{1,})[>]$/\1/'
	result="$result $(cat $file | grep -E "^[#]include [<].{1,}[>]$" | sed -E 's/^[#]include [<](.{1,})[>]$/\1/')"
done

echo "The most used $number libraries are:"

echo $result | awk '{
	for(i = 1;i < NF;i++){
		print $i
		}
	}' | uniq -c | sort -n | head -n $number
