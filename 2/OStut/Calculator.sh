#Tutorial Number: 02

#TITLE: Shell Scripting

#NAME:Bhushan Agrawal			ROLLNO:01

#CLASS:C                     BRANCH:Computer                         BATCH:C1

#DATE OF PERFORMANCE:20/01/2015

#!/bin/sh

num1=$1
num2=$2
temp=1

while [ $temp -eq 1 ]
do

echo "
1. Perform Addition
2. Perform Subtraction
3. Perform Multiplication
4. Perform Division
5. Perform Mod Operation
6. EXIT
"
#ch=0
flag=0
read ch

case $ch
in
1) echo -n "Addition is : "
   echo `expr $1 + $2`
   ;;

2) echo -n "Subtraction is : "
   echo `expr $1 - $2`
   ;;

3) echo -n "Multiplication is : "
   echo `expr $1 \* $2`
   ;;

4) echo -n "Division is : "
   echo `expr $1 / $2`
   ;;

5) echo -n "MOD is : "
   echo `expr $1 % $2`
   ;;
   
6) flag=$ch
   ;;

esac

if [ $flag -eq $ch ];then
break
fi

done
