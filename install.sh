#! /bin/bash

#Compile files
sudo g++ -std=c++11 -o load loader_demo.cc loader.o -lbfd


# Check if the compilation was successfully
if [ $? -ne 0 ]; then
	echo "Unable to comiple files"
fi


# Move files to /usr/bin
sudo mv bfd.h loader.h loader.o load /usr/bin

# Check if the move was successfully
if [ $? -eq 0 ]; then
	echo "Done successfully, ready to use."
else
	echo "failed to execute."
fi
