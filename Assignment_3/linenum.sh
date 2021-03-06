#!/bin/bash
# Ethan Hinkle - CS 270
# linenum.sh

# get the file that is to be edited
echo 'Enter the file you wish to edit:'
read file
# loop until 0 or 1 input
valid=0
while [ $valid -eq 0 ]
do
    echo 'Do you wish to add or remove line numbers? (1=add, 0=remove):'
    read choice
    if ( [[ $choice = "0" ]] || [[ $choice = "1" ]] )
    then
	valid=1
    else
	echo 'Invalid Input'
    fi
done
# adds line numbers using cat, writes to a temp file, clears original then adds them back
if [[ $choice = "1" ]]
then
    cat -n $file > temp.txt
    > $file
    cp temp.txt $file
    rm temp.txt
    exit 0
# removes all characters unitl \t character is found, only works for line numbers added via cat -n
elif [[ $choice = "0" ]]
then
    cut -d $'\t' -f 2- $file > temp.txt
    > $file
    cp temp.txt $file
    rm temp.txt
    exit 0
else
# error check msg
    echo 'Error'
fi
# should never run, just in case
exit 0
