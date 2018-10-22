#!/usr/bin/bash

globus_copy="/usr/bin/globus-url-copy" 
port=5000
output="/dev/null"
host="localhost"

function runCopyTest {
	ts=$(date +%s%N); 
	$globus_copy -bs $2 file://"$1" ftp://${host}:${port}${output};
	local tt=$((($(date +%s%N) - $ts)/1000000));

  echo "$tt"
}

if [[ "$1" == "-h" || "$1" == "--help" ]]; then
  echo "Usage: `basename $0` - Run a timing test by copying a file to a staging folder and recording the time for the copy
	
To run the script use 
$0 {source file} {#repeats}

e.g. 
$0 ~/Documents/test-src/test.txt 50"
  exit 0
fi

#if [ ! -d `eval echo "stagingArea"` ]; then
#	echo "staging folder doesn't exist so creating it to store temporary data"
#	mkdir "stagingArea"
#	> stagingArea/test.txt
#fi

if [ ! -d `eval echo "results"` ]; then
	echo "results folder doesn't exist so creating it to store results"
	mkdir "results"
fi

#clear the timings file
> results/timings.txt

source_file="$(cd "$(dirname "$1")"; pwd)/$(basename "$1")"

# repeat the test multiple times
echo "Running performance tests...."
echo "Block size" >> results/timings.txt
echo -e "GridFTP 4K\tGridFTP 32K\tGridFTP 128K\tGridFTP 512K" >> results/timings.txt
for value in $(eval echo {1..$2})
do
{ 
	echo -ne "Running test $value"'\r'
	tt_4k_src=`runCopyTest "$source_file" 4k`;
	tt_32k_src=`runCopyTest "$source_file" 32k`;
	tt_128k_src=`runCopyTest "$source_file" 128k`;
	tt_512k_src=`runCopyTest "$source_file" 512k`;
	echo -e "$tt_4k_src\t$tt_32k_src\t$tt_128k_src\t$tt_512k_src\t" >> results/timings.txt; 
} 
done

echo -e "\nDone"

