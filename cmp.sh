#!/bin/sh

if [ $# -eq 0 ];
then
	echo "need a file as param"
	exit;
else
	echo "(a invalid file hash will output macths for 0"
fi


echo "searching file $1"

#add hashs
HEADER=$(echo "action=cmp&hash=")
cat $1 |head -n 1000 |tail -n 400 |cut -f 1 |tr '\n' ';' > out.txt
DATA=$(cat out.txt)


curl --request POST "http://localhost:8888/pste/" --data $HEADER$DATA

rm out.txt

