#!/bin/sh

num=$1
sum=0
b1=$num
while [ $b1 -gt 0 ]
do
 b2=`expr $b1 % 10`
 #echo "$b2"
 echo -n $b2
 b1=`expr $b1 / 10`
 sum=`expr $sum + $b2`
done
echo
echo $sum
