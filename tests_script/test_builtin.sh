#/bin/bash
cmpdiff()
{
	diff -U 3 result/$1 result/$2 > result/diff.txt
	if [ $? -ne 0 ]; then
	    echo "${ROUGE}[KO]${RESETCOLOR} DIFF KO";
	else
		echo "${VERT}[OK]${RESETCOLOR} DIFF OK"
	fi
}

printdebug()
{
	if [ $PRINTDEBUG -eq 1 ]
	then
		echo "${CYAN}DEBUG :${RESETCOLOR}"
		if [ -s result/diff.txt ]
		then
			cat result/diff.txt
		else
			echo " DIFF output is empty :)"
		fi
	fi
}

dotest()
{
	cmpdiff $1 $2
	printdebug
}

##################### TEST NUM 11 #####################
echo " --- > TEST builtin cd 1 < ---"
echo "builtin cd simple"
echo "mkdir test && cd test ; touch a && touch b ; ls -la ; cd .. ; rm -rf test" | bash > result/b_27.out
echo "mkdir test && cd test ; touch a && touch b ; ls -la ; cd .. ; rm -rf test" | ../21sh > result/27.out
dotest b_27.out 27.out
echo " --- > TEST builtin cd 2 < ---"
echo "builtin cd error"
echo "cd testd" | bash > result/b_28.out
echo "cd testd" | ../21sh > result/28.out
dotest b_28.out 28.out
echo " --- > TEST builtin cd 2 < ---"
echo "builtin cd error"
echo "mkdir test/a/b/c/d/e/f ; cd test/a/b/c/d/e/f ; pwd ; rm -rf test" | bash > result/b_29.out
echo "mkdir test/a/b/c/d/e/f ; cd test/a/b/c/d/e/f ; pwd ; rm -rf test" | ../21sh > result/29.out
dotest b_29.out 29.out
echo " --- > TEST builtin cd home and - < ---"
echo "cd ; pwd ; cd - ; pwd" | bash > result/b_30.out
echo "cd ; pwd ; cd - ; pwd" | ../21sh > result/30.out
dotest b_30.out 30.out
echo " --- > TEST builtin cd home unset < ---"
echo "unset HOME ; cd" | bash > result/b_31.out
echo "unsetenv HOME ; cd" | ../21sh > result/31.out
dotest b_31.out 31.out
#######################################################
