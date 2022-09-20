#!bin/bash

for file in $@; do
	echo "$file:"
	cat $file | grep -Eo "(^| )?[1-9]*[02468]( |$)" | awk '{
	for(i=1;i<=NF;i++){
		if(!($i in fr))
			fr[$i]=0
		fr[$i]++
		}
	}
	END{
		for(elem in fr)
			print "number: " elem " freq: " fr[elem]
		}'
done
