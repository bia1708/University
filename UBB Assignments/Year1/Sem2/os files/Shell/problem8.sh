#!bin/bash

number=$1
shift 1

for file in $@; do
	echo "$file:"
	cat $file | awk -v var=$number '{
	for(i=1;i<=NF;i++)
		if($i!='\n'){
			if(!($i in fr))
				fr[$i]=0
			fr[$i]++
		}
	}
	END{
	for(elem in fr){
		if (fr[elem] > var)
			print "elem: "elem " freq: " fr[elem]
		}
	}'
done

