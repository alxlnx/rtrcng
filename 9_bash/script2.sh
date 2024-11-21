#!/bin/bash
# Написать подробные комментарии
cd ~
if [ -d dirs ]
then
  rm -r dirs
fi

num=$1
x=1
if [ -z "$num" ]; then
  echo "No input given, please submit an argument to this program." >&2
  exit 1
fi

mkdir dirs
cd dirs
while [ "$x" -le "$num" ];
do
  mkdir $x
  cd $x
  y=1
  while [ "$y" -le "$num" ];
  do
    mkdir $x$y
    echo "$x$y" > ./$x$y/$x$y
    y=$(( $y+1 ))
  done
  cd ..
  x=$(( $x+1 ))
done
 
