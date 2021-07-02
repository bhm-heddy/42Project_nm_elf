#!/bin/bash


DIR=script_test
FAIL=$DIR/fail


mkdir -p $DIR
mkdir -p $FAIL
for param in $@
do
	./my_nm $param 2>&1 > $DIR/my_$param.txt
	nm $param 2>&1 > $DIR/nm_$param.txt
	diff $DIR/my_$param.txt $DIR/nm_$param.txt >$DIR/ret.txt
	if [ $? -ne 0 ]; then
		mv $DIR/ret.txt $FAIL/$param.txt
		echo "FAIL -> [$param]"
	fi
done
