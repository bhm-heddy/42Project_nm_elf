#!/bin/bash

#IFS=':' read -r -a path_bin <<< "$PATH"

bin=( $(grep -rIL /usr/lib/*) )

rm -rf dir
mkdir dir
rm ret

for elem in "${bin[@]}"
do
	one=$elem
	echo "[  $one]"
	readelf -h $one >&- 2>&-
	if [ $? -eq 0 ]; then
		echo "   [TEST :]"
		name=${one##*/}
		./ft_nm $one > "dir/$name" 2>&1
		grep -E 'error|fault|bus|corrupt' "dir/$name"
		if [ $? -eq 0 ]; then
			echo " Failure -> [$name] " | tee >> ret
			sleep 2
		fi
	fi
done
