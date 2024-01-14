
#!/bin/bash

#features1 : add origin feature of git -- DONE
#--some optimisaiton may left
#but overall done
#
# BUG :: -o option will generate named file, 
# then when the script try to run a.out file
# it will throw error that file is not found..
#
#
#feature2 : add c++ compatiblity

# c_init(start)

if [ -d ~/.c ]
then 
	if [ -f ~/.c/file_name ]
	then
			:	
	else
			touch ~/.c/file_name
	fi

	if [ -f ~/.c/extended_lib ]
	then 
			:
	else
			touch ~/.c/extended_lib
	fi


else
		mkdir ~/.c
		touch ~/.c/file_name ~/.c/extended_lib
fi

# c_init(end)

if [ -f ./a.out ]
then
		rm a.out
fi

# do check wether optoins are given or files are given
string=""
extended=""
for item in $@
do
		string+=$item
		string+=" "
done

#compilation

if [ "$1" == "reset" ]
then
		echo "" > ~/.c/file_name
		echo "" > ~/.c/extended_lib
		exit
fi

if [ "$1" == "profile" ]
then
		echo -n "file name : "
		cat ~/.c/file_name
		echo -n "extended lib : "
		cat ~/.c/extended_lib
		exit
fi

if [ $# == 0 ]
then 
		head="$(cat ~/.c/file_name)"
		tail="$(cat ~/.c/extended_lib)"
		gcc $head $tail
		if [ $? != 0 ]
		then
			exit
		fi
		./a.out
		rm a.out
		exit

fi

if [ $# == 1 ]
then 
		head="$1"
		tail="$(cat ~/.c/extended_lib)"
		gcc $head $tail
		if [ $? != 0 ]
		then
			exit
		fi
		echo "$1" > ~/.c/file_name
		./a.out
		rm a.out
		exit
fi


gcc $string



if [ $? != 0 ]
then
	exit 
else
	echo "$1" > ~/.c/file_name
	for newitem in $@
	do
			if [ "$1" != "$newitem"  ]
			then
				extended+=$newitem
			fi
	done
	echo "$extended" > ~/.c/extended_lib
	./a.out
	rm a.out
	exit
fi



# origin feature structure
#
# IF entered c  then run the previous file with same extented lib
# IF enetered file name only then run <file_name> with same extented lib
#
# c -reset option to flush the buffer
#
# FILE STURCTURE
#
# ~/c dir
# contain files -- 1. prev file name | 2. prev extended lib
