#!/bin/sh

for i in `ls $HOME`
do
	if [ -f $i ];then
		echo $i >> fff.txt
	fi
done
