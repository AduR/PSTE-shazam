#!/bin/sh

file_in_full=$1
NB=$2

echo "loading file $NB - $file_in_full"

# add music
curl --request POST 'http://localhost:8888/pste/' --data 'action=addMusic&title='$file_in_full

#add hashs
HEADER=$(echo "action=addHash&musicId="$NB"&hash=")
DATA=$(cut -f 1 $file_in_full |tr '\n' ';')

curl --request POST "http://localhost:8888/pste/" --data $HEADER$DATA

echo "$NB done. next."

