#!/bin/bash
# Ethan Hinkle - CS 270
# backup.sh

# checks working directory for .backup with directory path, if not creates it
# path="/.backup"
# printf "${PWD}${path}" full path of .backup
if [[ ! -d .backup ]]
then
    mkdir .backup
fi
# loops through all files and directories in the current directory
for file in *
do
# remove duplicate files
    if [[ -f .backup/$file ]] || [[ -d .backup/$file ]]
    then
	rm -r .backup/$file
    fi
    cp -r $file .backup/$file
done

exit 0
