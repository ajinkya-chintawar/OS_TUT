                      

Question 4:Check whether the string is pallindrome or not.

ch=1
while [ $ch -eq 1 ]
do
 echo "Enter a String"
 read str
 flag=0
 len=`echo $str | wc -c`
 len=`expr $len - 1`
 i=1
 while [ $i -lt $len ]
 do
   c1=`echo $str | cut -c $i`
   c2=`echo $str | cut -c $len` 
   if [ $c1 != $c2 ]
    then 
      flag=1
      break;
   fi
   i=`expr $i + 1`
   len=`expr $len - 1`
 done

 if [ $flag -eq 1 ] 
 then
   echo "String is not a Palindrome"
 else
   echo "String is Palindrome"
 fi
 echo "Do you want to continue (1/0)?"
 read ch
done      


output-
prajkta@prajkta-laptop:~/Desktop$ sh palindrome.sh
Enter a String
abcd
String is not a Palindrome
Do you want to continue (1/0)?
1
Enter a String
abba
String is Palindrome
Do you want to continue (1/0)?
0


