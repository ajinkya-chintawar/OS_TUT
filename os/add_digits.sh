#!/bin/bash
#tut2 part 2 addition of digits of a number

echo "enter the number :"
read number
i=1
length=${#number}
sum=0
while [ $i -le $length ]
	do
		rem=`expr $number % 10`		
		number=`expr $number / 10`
		sum=`expr $sum + $rem`
		i=`expr $i + 1`
done
	echo "sum = $sum"
		
