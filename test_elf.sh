#!/bin/bash


path_g="elf/good"

good=( $(ls -1 $path_g) )

for elem in "${good[@]}"
do
		echo [$path_g/$elem]
		readelf -h $path_g/$elem >&- 2>&-
		if [ $? -eq 0 ]; then
			echo "elf ok !"
			nm $path_g/$elem > a
			./my_nm $path_g/$elem > b
			diff -q a b
			if [ $? -eq 1 ]; then
				echo "Error : $path_g/$elem !!!!!!!!!!!!!!!!!!!!!!!"
				#exit 1
			fi
		echo -e "Next!\n----\n"
		fi
done

echo -e "------------\n------------\n------------\nBAD:\n"

path_g="elf/bad"

good=( $(ls -1 $path_g) )



for elem in "${good[@]}"
do
		echo [$path_g/$elem]
#		readelf -h $path_g/$elem >&- 2>&-
		if [ $? -eq 0 ]; then
			echo "elf ok !"
			nm $path_g/$elem > a
			./my_nm $path_g/$elem > b
			diff -q a b
			if [ $? -eq 1 ]; then
				echo "Error : $path_g/$elem !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
#				exit 1
			fi
		echo -e "Next!\n----\n"
		fi
done
