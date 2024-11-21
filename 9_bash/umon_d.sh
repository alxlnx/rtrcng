# !/bin/bash
# Написать подробные комментарии
if [ $# -ge 0 ];
then
  disk="sda"
else
  disk=$1
fi
String=$(stat $1 1 2)
echo ${String: -6} 
