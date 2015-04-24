               Tutorial Number: 02
TITLE: Shell Programming.
NAME:	Yamini Patil		ROLLNO:21
CLASS:  D                   BRANCH:  Comp                    BATCH: 2nd
DATE OF PERFORMANCE:14-08-2013

Question :write shell script tp reverse integer and calculate sum of digits.               


echo "Enter the number\n"
read a
b=$a
echo "Reversed number is : "
while [ $a -gt 0 ]
do
r=`expr $a % 10`
echo -n $r
a=`expr $a / 10`
done


echo "\nSum of digits of the number is : "
sum=0
while [ $b -gt 0 ]
do
r=`expr $b % 10`
sum=`expr $r + $sum`
b=`expr $b / 10`
done
echo $sum

output-
ted-21@unix08-OptiPlex-360:~/Desktop$ sh reverse.sh
Enter the number
12345
Reversed number is : 
54321
Sum of digits of the number is : 
15


