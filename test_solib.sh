#!/bin/bash


path_g="/usr/lib"

good=( $(find $path_g -name "*.so") )

for elem in "${good[@]}"
do
		echo [$elem]
		if [ $? -eq 0 ]; then
			echo "elf ok !"
			nm $elem > a
			./my_nm $elem > b
			diff -q a b
			if [ $? -eq 1 ]; then
				echo "Error : $elem !!!!!!!!!!!!!!!!!!!!!!!"
				#exit 1
			fi
		echo -e "Next!\n----\n"
		fi
done
