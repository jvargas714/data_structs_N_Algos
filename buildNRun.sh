#!/bin/bash 
## simple script to build and run a cpp file 
## Usage: ./buildNRun.sh source.cpp exeName

cppFile=$1
exeName=$2

if [ -e $exeName ]; then 
	rm -v $exeName
fi

g++ -Wall -std=c++11 $cppFile -o $exeName

if [ $? -ne 0 ]; then 
	echo "Error during compilation, exiting..."
	exit 99
fi

printf "Executing $exeName...\n\n"
clear
./$exeName
exit $?

