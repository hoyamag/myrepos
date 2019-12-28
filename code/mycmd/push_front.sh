#!/bin/bash
# $1 file path
# $2 file path
# $2 is overwroten by text that is concatenation of $1 and $2
tmpfile=$(mktemp)
cat $1 $2 > tmpfile
cat tmpfile > $2
echo $tmpfile
rm $tmpfile

