#!/bin/bash

./my_nm $1 > a
nm $1 > b
diff a b > reta_b.txt
