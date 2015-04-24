#/bin/sh

echo "Number of elements : "
read num

echo "Enter the elements : "
for((i=0; i<num; ++i))
do
	read arr[$i]	
done

for((i=0; i<num; ++i))
do
	for((j=0; j<num-1; ++j))
	do
		if [ ${arr[$j]} -gt ${arr[$j+1]} ]
		then
			temp=${arr[$j]}
			arr[$j]=${arr[$j+1]}
			arr[$j+1]=$temp			
		fi	
	done
done

echo "Sorted elements are : "
for((i=0; i<num; ++i))
do
	echo ${arr[$i]}
done	
