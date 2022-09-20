#!/bin/bash

for arg in $@; do
        if [ -d $arg ]; then
                stat -c"Owner: %U" $arg
                filename=""
                max_size=0
                for file in $(find $arg -type f); do
                        filesize=$(wc -c $file | cut -d" " -f1)
                        if [ "$filesize" -gt "$max_size" ]; then
                             max_size=$filesize
                             filename=$file
                        fi
                done
                echo $filename $max_size
        elif [ -f $arg ]; then
                reverse=""
                while read line; do
                        reverse="$line\n$reverse"
                done<$arg
                printf $reverse
        else
                echo "Invalid argument!"
                exit
        fi
done
