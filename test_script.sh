#!/bin/bash

IFS=':' read -r -a path_bin <<< "$PATH"

for elem in "${path_bin[@]}"
do
	list_bin=( $(ls -1 $elem) )
	for bin in "${list_bin[@]}"
	do

		echo $elem/$bin
		readelf -h $elem/$bin >&- 2>&-
		if [ $? -eq 0 ]; then
			nm $elem/$bin > a
			./ft_nm $elem/$bin > b
			diff -q a b
			if [ $? -eq 1 ]; then
				echo "Error : $elem/$bin"
#				exit 1
			fi
		echo Ok!
		fi
	done
done

