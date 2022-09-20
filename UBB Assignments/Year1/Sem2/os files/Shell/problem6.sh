#!bin/bash

file=$1
shift 1

for username in $@; do
	if echo $username | grep -Eq "^[a-z]{4}[0-9]{4}$"
	then
		echo $username
		for word in $(cat $file); do
			if find $word -path '*/$username'>/dev/null 2>/dev/null
			then
				find $word -path '*/$username'
				echo $word
			else
				echo "No rights"
			fi
		done
	fi
done
