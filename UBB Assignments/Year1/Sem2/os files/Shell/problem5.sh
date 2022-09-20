#!bin/bash

file1=$1
file2=$2
shift 2

echo "Wrong usernames:" > $file2

cat $file1 | grep -Ev "^[a-z]{4}[0-9]{4}$" >> $file2


