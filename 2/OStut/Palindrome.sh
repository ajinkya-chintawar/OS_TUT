#!/bin/sh

String=$1
len=${#String}

i=1;flag=0
mid=`expr $len / 2`
temp=$len

while [ $i -le $mid ]
do
 ch1=`echo $String|cut -c $i`
 ch2=`echo $String|cut -c $len`
 
 if [ $ch1 != $ch2 ];then
  flag=1
  break;
 fi
 
 i=`expr $i + 1`
 len=`expr $len - 1`
done

if [ $flag -eq 1 ];then
 echo "Not Palindrome"
else 
 echo "Palindrome"
fi

#student@admin49-OptiPlex-360:~/Desktop$ ./Palindrom.sh nitin
#Palindrome
#student@admin49-OptiPlex-360:~/Desktop$ ./Palindrom.sh niti
#Not Palindrome

