#!/bin/bash
## script to clean, build, etc etc 

if [ $# -ne 1 ]; then 
	echo "must provide one argument..."
	exit 1
fi

cmd=$1

if [ $cmd == "clean" ]; then
	printf "Cleaning build files\n\n"
	sleep 2
	cd ./cpp
	make clean
	cd -
	find . -name "cmake_install.cmake" \
	-or -name "*CMakeCache*" \
	-or -name "CMakeFiles*"\
	-or -name "Makefile"\
	-or -name "*.o"\
	-or -name "bin" | xargs rm -rfv 

elif [ $cmd == "all" ]; then 
	cd ./cpp;
	cmake CMakeLists.txt
	if [ $? -ne 0 ]; then 
		printf "\nThere was an error building...\n\n"
		exit 2
	fi
	make all
	if [ $? -ne 0 ]; then 
		printf "\nThere was an error building, check build.log..."
		exit 5
	fi
	cd -
	
else 
	printf "\nUnknown command :(\n\n"
	exit 3
fi

exit 0

