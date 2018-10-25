#!/usr/bin/env bash

echo 'Running fuse client script'
cd $1
echo `pwd`
./dms-fuse-client -d $2 $3