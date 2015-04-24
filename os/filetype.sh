#!/bin/bash
#tut2 part 1

echo "enter any filename:"
read filename

if [ -d $filename ]
then
	echo "directory"
else
	echo " It is not directory :"	
	echo " Check for another types of file :"
	type=`ls -l $filename|cut -c 1`
	echo "filetype is = $type so :"

	case $type in 
		
		b) echo "$filename is block file type";;
		c) echo "$filename is character file type";;
		s) echo "$filename is socket file type";;
		l) echo "$filename is link file type";;
		-) echo "$filename is ordinary file type";;
		*) echo "$filename is of no type";;
	esac
fi

if [ -r $filename ]
then
	echo "$filename is readable."
elif	[ -w $filename ]
then
	echo "$filename is writable."
elif [ -x $filename ]
then
	echo "$filename is executable."
fi
