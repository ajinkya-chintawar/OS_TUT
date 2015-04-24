for i in `echo $HOME|ls`
do
	if [ -f $i ] 
	then 
		echo $i >>ff.txt
	fi 
done
line=`wc -l ff.txt | cut -d " " -f 1`
#echo $line

c=1
max=0

while [ $c -lt $line ]
do
	filename=`head -$c ff.txt | tail -1`
	s=`ls -l $filename | tr -s " " | cut -d " " -f 5`
	if [ -z $s ]
	then
		s=0
	fi
	if [ $s -gt $max ]
	then
		max=`echo $s`
		mf=`ls -l $filename | tr -s " " | cut -d " " -f 9`
	fi
c=`expr $c + 1`
done

echo "The File With The Max File Size Is : "$mf $max

#Output :-
#samsung@samsung-PC ~$ bash size1.sh
#The File With The Max File Size Is : mongodb-win32-x86­642008 #plus-2.6.5-signed.msi 138409472
