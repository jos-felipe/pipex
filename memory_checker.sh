#!/bin/bash

# This script is used to check memory leaks of the program

# Name of the program
NAME=./pipex_debug
TESTS_PATH=./tests
INFILE=$TESTS_PATH/infile.txt
NO_READ_FILE=$TESTS_PATH/no_read_perm.txt
OUTFILE=$TESTS_PATH/outfile.txt
VALGRIND_LOG=$TESTS_PATH/valgrind.log

# Colors Definition 
GREEN="\033[32;1m"
RED="\033[31;1m"
CYAN="\033[36;1;3;208m"
WHITE="\033[37;1;4m"
COLOR_LIMITER="\033[0m"

# Path and filenames for the test files
mkdir -p $TESTS_PATH
ls --help > $INFILE
touch $NO_READ_FILE
chmod -r $NO_READ_FILE

# Compile the program in debug mode
make debug

# Test 1 - Success case
echo -e $GREEN"[Success case]"$COLOR_LIMITER
valgrind	--leak-check=full \
			--show-reachable=yes \
			--track-fds=yes \
			--show-leak-kinds=all -s \
			--track-origins=yes \
			--log-file=$VALGRIND_LOG \
 $NAME $INFILE "cat" "grep call" $OUTFILE > /dev/null 2>&1
cat $VALGRIND_LOG | grep "All heap blocks were freed -- no leaks are possible" > /dev/null
if [ $? -eq 0 ]; then
	echo -e $GREEN"[OK]"$COLOR_LIMITER;
else
	echo -e $RED"[KO]"$COLOR_LIMITER;
fi

# Test 2 - Non-existent input file
TMP=$INFILE
INFILE=non_existent_file
echo -e $GREEN"[Non-existent input file]"$COLOR_LIMITER
valgrind	--leak-check=full \
			--show-reachable=yes \
			--track-fds=yes \
			--show-leak-kinds=all -s \
			--track-origins=yes \
			--log-file=$VALGRIND_LOG \
 $NAME $INFILE "cat" "grep call" $OUTFILE > /dev/null 2>&1
cat $VALGRIND_LOG | grep "All heap blocks were freed -- no leaks are possible" > /dev/null
if [ $? -eq 0 ]; then
	echo -e $GREEN"[OK]"$COLOR_LIMITER;
else
	echo -e $RED"[KO]"$COLOR_LIMITER;
fi
INFILE=$TMP

# Test 3 - Infile with no read permission
TMP=$INFILE
INFILE=$NO_READ_FILE
echo -e $GREEN"[Infile with no read permission]"$COLOR_LIMITER
valgrind	--leak-check=full \
			--show-reachable=yes \
			--track-fds=yes \
			--show-leak-kinds=all -s \
			--track-origins=yes \
			--log-file=$VALGRIND_LOG \
 $NAME $INFILE "cat" "grep call" $OUTFILE > /dev/null 2>&1
cat $VALGRIND_LOG | grep "All heap blocks were freed -- no leaks are possible" > /dev/null
if [ $? -eq 0 ]; then
	echo -e $GREEN"[OK]"$COLOR_LIMITER;
else
	echo -e $RED"[KO]"$COLOR_LIMITER;
fi
INFILE=$TMP

# Test 4 - Invalid cmd1
echo -e $GREEN"[Invalid cmd1]"$COLOR_LIMITER
valgrind	--leak-check=full \
			--show-reachable=yes \
			--track-fds=yes \
			--show-leak-kinds=all -s \
			--track-origins=yes \
			--log-file=$VALGRIND_LOG \
 $NAME $INFILE "invalid_cmd1" "grep call" $OUTFILE > /dev/null 2>&1
cat $VALGRIND_LOG | grep "All heap blocks were freed -- no leaks are possible" > /dev/null
if [ $? -eq 0 ]; then
	echo -e $GREEN"[OK]"$COLOR_LIMITER;
else
	echo -e $RED"[KO]"$COLOR_LIMITER;
fi

# Test 5 - Invalid cmd2
echo -e $GREEN"[Invalid cmd2]"$COLOR_LIMITER
valgrind	--leak-check=full \
			--show-reachable=yes \
			--track-fds=yes \
			--show-leak-kinds=all -s \
			--track-origins=yes \
			--log-file=$VALGRIND_LOG \
 $NAME $INFILE "cat" "invalid_cmd2" $OUTFILE > /dev/null 2>&1
cat $VALGRIND_LOG | grep "All heap blocks were freed -- no leaks are possible" > /dev/null
if [ $? -eq 0 ]; then
	echo -e $GREEN"[OK]"$COLOR_LIMITER;
else
	echo -e $RED"[KO]"$COLOR_LIMITER;
fi

# Test 6 - Invalid outfile
TMP=$OUTFILE
OUTFILE=/etc/passwd
echo -e $GREEN"[Invalid outfile]"$COLOR_LIMITER
valgrind	--leak-check=full \
			--show-reachable=yes \
			--track-fds=yes \
			--show-leak-kinds=all -s \
			--track-origins=yes \
			--log-file=$VALGRIND_LOG \
 $NAME $INFILE "cat" "grep call" $OUTFILE > /dev/null 2>&1
cat $VALGRIND_LOG | grep "All heap blocks were freed -- no leaks are possible" > /dev/null
if [ $? -eq 0 ]; then
	echo -e $GREEN"[OK]"$COLOR_LIMITER;
else
	echo -e $RED"[KO]"$COLOR_LIMITER;
fi
OUTFILE=$TMP