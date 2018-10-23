#!/usr/bin/bash

globus_copy="/usr/bin/globus-url-copy" 
port=5000
output="/dev/null"
host="localhost"

function runCopyTest {
	ts=$(date +%s%N); 
	$globus_copy file://"$1" ftp://${host}:${port}${output};
	local tt=$((($(date +%s%N) - $ts)/1000000));

  echo "$tt"
}

if [[ "$1" == "-h" || "$1" == "--help" ]]; then
  echo "Usage: `basename $0` - Run a timing test by copying the input file from the host server to the destination server using gridFTP and recording the time taken for the copy

To run the script use 
$0 {source file} {#repeats}

e.g. 
$0 ~/Documents/test-src/test.txt 50"
  exit 0
fi

if [ ! -d `eval echo "results"` ]; then
	echo "results folder doesn't exist so creating it to store results"
	mkdir "results"
fi

#clear the timings file
> results/timings.txt

source_file="$(cd "$(dirname "$1")"; pwd)/$(basename "$1")"

# repeat the test multiple times
echo "Running performance tests...."
echo -e "GridFTP copy" >> results/timings.txt
for value in $(eval echo {1..$2})
do
{ 
	echo -ne "Running test $value"'\r'
	tt_gridFTP=`runCopyTest "$source_file"`;
	echo -e "$tt_gridFTP\t" >> results/timings.txt; 
} 
done

echo -e "\nDone"

