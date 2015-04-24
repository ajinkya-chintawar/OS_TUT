#/bin/bash

str=$1
len=${#str}

mid=`expr $len / 2`
i=1
flag=0

while [ $i -le $mid ]
do
	ch1=`echo $str|cut -c $i`
	ch2=`echo $str|cut -c $len`
	
	if [ $ch1 != $ch2 ]
	then
		flag=1
		break;	
	fi

	i=`expr $i + 1`
	len=`expr $len - 1`

done

if [ $flag -eq 1 ] 
then
	echo "Not Palindrome"
else
	echo "Palindrome"
fi
