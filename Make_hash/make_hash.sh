#!/bin/sh

MUSIC_PATH="../../musiques"
PROG_NAME=make_hash

NB=1

mkdir Hash

for file_in_full in $(find $MUSIC_PATH -iname '*.wav'); 
do
	echo ""
	echo "====="
	echo $NB
	file_in_namefull=$(basename "$file_in_full")
	file_in_nameshort="${file_in_namefull%.*}"
	file_out_path=hash/$file_in_nameshort.txt
	echo "$file_in_full > $file_out_path"
	time ./$PROG_NAME $file_in_full > $file_out_path
	(( NB=NB+1 ))
done

