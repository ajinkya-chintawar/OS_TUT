#!/bin/sh

FileName=$1

if [ -e $1 ];then
 echo "File Exists"
 FileListing=`ls -l $1`

 FileType=`echo $FileListing|cut -c 1`

 if [ -d $FileName ];then
  echo "Directory"
 fi

 case $FileType in
 -) echo "Regular File";;
 b) echo "Block Device File";;
 c) echo "Character Device File";;
 l) echo "Symbolic Link File";;
 s) echo "Socket File";;
 esac

 if [ -r $FileName ];then
  echo "Read Permission"
 elif [ -w $FileName ];then
  echo "Write Permission"
 elif [ -x $FileName ];then
  echo "Execute Permission"
 else
  echo "Absent" 
 fi

else
 echo "File Does Not Exist"
fi
