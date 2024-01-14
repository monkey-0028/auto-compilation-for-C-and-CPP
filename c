#!/bin/bash
# dir tree
# ./c --  main folder
# 
# prev_file -- contain address of previous compiled file
# extended -- contain extended line of compilation code
# compiler -- contain name of comiler to use 
# editor -- contain name of editor to use
#

# --------------------------------INIT --START------------------------------------
if [  -d ~/.c ]
then
		if [ ! -f ~/.c/prev_file ]
		then
				touch ~/.c/prev_file    # created prev_file
		fi
		if [ ! -f ~/.c/extended ]
		then
				touch ~/.c/extended   # created extended file
		fi
		if [ ! -f ~/.c/compiler ]
		then
				touch ~/.c/compiler   # created compiler file
		fi
		if [ ! -f ~/.c/editor ]
		then
				touch ~/.c/editor     # created editor file
		fi
else
		mkdir ~/.c
		maindir=~/.c
		touch $maindir/prev_file $maindir/extended $maindir/compiler $maindir/editor
fi
maindir=~/.c
check_temp=$(cat $maindir/compiler)

if [ "$check_temp" == "" ]
then
		echo -n "gcc" > $maindir/compiler            # default compiler
fi

if [ "$(cat $maindir/editor)" == "" ]
then
		echo -n "vim" > $maindir/editor          # defalut editor
fi

rm a.out &>/dev/null
# ---------------------------------INIT -- END -----------------------------------------------

if [ $# == 1 ]
then
		if [ "$1" == "-profile"  ] 			# profile command
		then
				echo -n "file name : "
				cat $maindir/prev_file ; echo ""
				echo -n "extended lib : "
				cat $maindir/extended ; echo ""
				echo -n "compiler : "
				cat $maindir/compiler ; echo ""
				echo -n "editor : "
				cat $maindir/editor ; echo ""
				exit 
		fi
		
		if [ "$1" == "-reset" ] 			# reset command
		then
				echo -n "" > $maindir/prev_file
				echo -n "" > $maindir/extended
				echo -n "" > $maindir/editor
				echo -n "gcc" > $maindir/compiler
				exit
		fi
		
		if [ "$1" == "-cc" ] 			# change compiler
		then
				echo -n "compiler : ";
				cat $maindir/compiler
				echo ""
				echo -n "new compiler : "
				read new_compiler
				temp=$new_compiler
				echo -n "$temp" > $maindir/compiler
				
				if [ "$?" == 0 ]
				then
						echo "compiler updated successfully"
				else
						echo "process failed"
				fi
				
				exit
		fi

		if [ "$1" == "-ex" ]
		then
				echo -n "" > $maindir/extended
				echo "Lib extension cleared!!"
				exit
		fi

		if [ "$1" == "-ce" ]			# change editor
		then
				echo -n "editor : "
				cat $maindir/editor
				echo ""
				echo -n "new editor : "
				read new_editor
				echo -n "$new_editor" > $maindir/editor

				if [ "$?" == 0 ]
				then
						echo "editor changed successfully"
				else
						echo "failed to change editor"
				fi
				exit
		fi

		
		if [ "$1" == "$(cat $maindir/editor)" ]               # launching editor( $# = 1 )
		then
				var_file="$(cat $maindir/prev_file)"
				var_extended="$(cat $maindir/extended)"
				var_compiler="$(cat $maindir/compiler)"
				$1 $var_file
				if [ "$?" == 0 ]
				then
						$var_compiler $var_file $var_extended
						if [ "$?" == 0 ]
						then
								./a.out
								rm a.out
						fi
				else
						echo "Failed to open the editor"
				fi
				
				exit
		fi
		#filename
		var_compiler=$(cat $maindir/compiler)
		var_extended=$(cat $maindir/extended)
		$var_compiler $1 $var_extended
		if [ "$?" == 0 ]
		then
				./a.out
				rm a.out
				echo -n "$1" > $maindir/prev_file
				exit
		fi

elif [ $# == 0 ]
then
		var_file="$(cat $maindir/prev_file)"
		var_compiler="$(cat $maindir/compiler)"
		var_extended="$(cat $maindir/extended)"

		$var_compiler $var_file $var_extended

		if [ $? == 0 ]
		then
				./a.out
				rm a.out
		fi
		exit
else 
		# c <file_name> -extension
		# c vim <file_name>
		# c vim <file_name> -extension
		# 1 -- file/editor
		# 2 -- file/extesion
		# 3.. -- extension
		if [ "$1" == "$(cat $maindir/editor)" ]
		then
				# 2 is file then
				var_compiler="$(cat $maindir/compiler)"
				var_extended=""
				if [ "$3" == "" ]
				then
						var_extended="$(cat $maindir/extended)"
				else
						for item in $@
						do
								if [[ "$item" != "$1" && "$item" != "$2" ]]
								then
									var_extended+="$item "
								fi
						done

				fi
				
				$1 $2 $var_extended    # opening the editor with file
				
				if [ "$?" != 0 ]
				then
						echo "failed to launch editor!!"
						exit
				fi

				$var_compiler $2 $var_extended   # compiling here!!

				if [ "$?" == 0 ]
				then
						./a.out
						rm a.out
						echo -n "$2" > $maindir/prev_file
						echo -n "$var_extended" > $maindir/extended

				fi
				
				exit
		else
				# 1 -- is file name
				# rest is extension
				var_compiler="$(cat $maindir/compiler)"
				var_extended=""
				for item in $@
				do
						if [ "$item" != "$1" ]
						then
							var_extended+="$item "
						fi
				done
				
				$var_compiler $1 $var_extended  

				if [ $? == 0 ]
				then
						./a.out
						rm a.out
						echo -n "$1" > $maindir/prev_file
						echo -n "$var_extended" > $maindir/extended
				fi


				
		fi

fi




















