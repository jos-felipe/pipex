#!/bin/bash

# This script is used to test the functionality of the program

# Name of the program
NAME=./pipex
TMP=./tests

# Colors Definition 
GREEN="\033[32;1m"
RED="\033[31;1m"
CYAN="\033[36;1;3;208m"
WHITE="\033[37;1;4m"
COLOR_LIMITER="\033[0m"

# Path and filenames for the test files
mkdir -p $TMP
ls --help > $TMP/infile.txt
touch $TMP/no_read_perm.txt
chmod -r $TMP/no_read_perm.txt

# Compile the program
make

# Test 1 - Success case
echo -e $GREEN"[Success case]"$COLOR_LIMITER
$NAME $TMP/infile.txt "cat" "grep call" $TMP/outfile.txt; echo $? > $TMP/exit.txt
< $TMP/infile.txt cat | grep call > $TMP/outfile_ref.txt; echo $? > $TMP/exit_ref.txt
if diff $TMP/outfile.txt $TMP/outfile_ref.txt && diff $TMP/exit.txt $TMP/exit_ref.txt; then 
	echo -e $GREEN"[OK]"$COLOR_LIMITER; 
else 
	echo -e $RED"[KO]"$COLOR_LIMITER; 
fi

# Test 2 - Non-existent input file
echo -e $GREEN"[Non-existent input file]"$COLOR_LIMITER
$NAME non_existent_file "cat" "grep call" $TMP/outfile.txt; echo $? > $TMP/exit.txt
< non_existent_file cat | grep call > $TMP/outfile_ref.txt; echo $? > $TMP/exit_ref.txt
if diff $TMP/outfile.txt $TMP/outfile_ref.txt && diff $TMP/exit.txt $TMP/exit_ref.txt; then 
	echo -e $GREEN"[OK]"$COLOR_LIMITER; 
else 
	echo -e $RED"[KO]"$COLOR_LIMITER; 
fi

# Test 3 - Infile with no read permission
echo -e $GREEN"[Infile with no read permission]"$COLOR_LIMITER
$NAME $TMP/no_read_perm.txt "cat" "grep call" $TMP/outfile.txt; echo $? > $TMP/exit.txt
< $TMP/no_read_perm.txt | grep call > $TMP/outfile_ref.txt; echo $? > $TMP/exit_ref.txt
if diff $TMP/outfile.txt $TMP/outfile_ref.txt && diff $TMP/exit.txt $TMP/exit_ref.txt; then 
	echo -e $GREEN"[OK]"$COLOR_LIMITER; 
else 
	echo -e $RED"[KO]"$COLOR_LIMITER; 
fi

# Test 4 - Non-existent cmd1
echo -e $GREEN"[Non-existent cmd1]"$COLOR_LIMITER
$NAME $TMP/infile.txt "non_existent_cmd1" "grep COLS" $TMP/outfile.txt; echo $? > $TMP/exit.txt
< $TMP/infile.txt non_existent_cmd1 | grep COLS > $TMP/outfile_ref.txt; echo $? > $TMP/exit_ref.txt
if diff $TMP/outfile.txt $TMP/outfile_ref.txt && diff $TMP/exit.txt $TMP/exit_ref.txt; then 
	echo -e $GREEN"[OK]"$COLOR_LIMITER; 
else 
	echo -e $RED"[KO]"$COLOR_LIMITER; 
fi

# Test 5 - Non-existent cmd2
echo -e $GREEN"[Non-existent cmd2]"$COLOR_LIMITER
$NAME $TMP/infile.txt "cat" "non_existent_cmd2" $TMP/outfile.txt; echo $? > $TMP/exit.txt
< $TMP/infile.txt cat | "non_existent_cmd2" > $TMP/outfile_ref.txt; echo $? > $TMP/exit_ref.txt
if diff $TMP/outfile.txt $TMP/outfile_ref.txt && diff $TMP/exit.txt $TMP/exit_ref.txt; then 
	echo -e $GREEN"[OK]"$COLOR_LIMITER; 
else 
	echo -e $RED"[KO]"$COLOR_LIMITER; 
fi

# Test 6 - Invalid outfile
echo -e $GREEN"[Invalid outfile]"$COLOR_LIMITER
$NAME $TMP/infile.txt "cat" "grep call" /etc/passwd; echo $? > $TMP/exit.txt
< $TMP/infile.txt cat | grep call > /etc/passwd; echo $? > $TMP/exit_ref.txt
if diff $TMP/outfile.txt $TMP/outfile_ref.txt && diff $TMP/exit.txt $TMP/exit_ref.txt; then 
	echo -e $GREEN"[OK]"$COLOR_LIMITER; 
else 
	echo -e $RED"[KO]"$COLOR_LIMITER; 
fi