#!/bin/bash
#tut2 part 3 sorting even and odd numbers in two different files

rm even.txt
rm odd.txt

echo "enter filename"
read filename

line_no=`wc -l < $filename`
i=1

while [ $i -le $line_no ]
do
	line=`head -$i $filename|tail -1`
	rem=`expr $line % 2`
	
	if [ $rem -eq 0 ]
	then
		echo "$line" >> even.txt
	else
		echo "$line" >> odd.txt
	fi
	
	i=`expr $i + 1`
done
	
