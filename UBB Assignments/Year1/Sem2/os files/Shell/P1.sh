#!/bin/bash

if [ $# -lt 2 ]; then
        echo "bad"
        exit
fi


username=$1
shift 1


if !( grep -Eq "$username" /etc/passwd); then
        echo "bad user"
        exit
fi 2>/dev/null


fullname=$(
grep -E "$username" /etc/passwd | awk -F: '{
        print $5
        }')


counter=0
for dir in $@; do
        for line in $(ls -AlR $dir | grep -E "$username" | grep -oE " \.[a-z]{1,}$" | uniq -u); do
                counter=$((counter+1))
        done
done

echo "$fullname: $counter hidden file(s)"
