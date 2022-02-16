#!/bin/bash

# If the numbers of arguments ($#) is not (-ne) 2, display usage and
# exit with err code 1.

if [ $# -ne 2 ]; then
	echo "Invalid number of arguments." 
	echo "Usage : ./randomizer.sh <a> <b>."
	echo "Where a-b is the range."
	exit 1
fi

# Using seq to generate a sequence of numbers, shuf to permute lines randomly,
# tr to replace new line by space, and sed to remove the space at the end.
# Use it on your push swap like so :
#
#     ./push_swap $(./randomizer.sh 0 10)

echo -n "tester "
seq $1 $2 | shuf | tr '\n' ' ' | sed -r 's/.$//'
