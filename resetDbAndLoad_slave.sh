#!/bin/sh

file_in_full=$1
NB=$2

echo "loading file $NB - $file_in_full"

curl --request POST 'http://localhost:8888/pste/' --data 'action=addMusic&title='$file_in_full
	
time cut -f 1 $file_in_full |xargs -L1 -I '{}' curl --request POST 'http://localhost:8888/pste/' --data 'action=addHash&musicId='$NB'&hash='{}''

echo "done. next."

