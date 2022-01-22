#!/bin/bash
# Ethan Hinkle - CS 270
# rmvunderscore.sh

# get all files in the current directory
for file in *
do
# checks if the file is a c/c++ file via wildcard
    if ( [[ "$file" == *.c ]] || [[ "$file" == *.cpp ]] )
    then
# checks if the file has an underscore by removing the underscore
# then checking for if the file still exists, if not !0, so 1
	if [[ ! -f ${file//_/} ]]
	then
# rename via move to file with new name
	    mv $file ${file//_/}
	fi
    fi
done
exit 0
