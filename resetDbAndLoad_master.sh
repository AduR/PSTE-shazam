#!/bin/sh

HASH_PATH="./Hash"
NB=1

echo "reseting database"
curl --request POST 'http://localhost:8888/pste/' --data 'action=clear'
echo "start loading musics and hashs"

for file_in_full in $(find $HASH_PATH -iname '*.txt'); 
do
	time sh resetDbAndLoad_slave.sh $file_in_full $NB

	sleep 2
	NB=$[NB + 1]
done

