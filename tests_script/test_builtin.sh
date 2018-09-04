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
	echo " =========================== "
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
echo "mkdir -p test/a/b/c/d/e/f ; cd test/a/b/c/d/e/f ; pwd ; rm -rf test" | bash > result/b_29.out
echo "mkdir -p test/a/b/c/d/e/f ; cd test/a/b/c/d/e/f ; pwd ; rm -rf test" | ../21sh > result/29.out
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

##################### TEST NUM 12 #####################
echo " --- > TEST builtin cd 1 < ---"
echo "builtin env error"
echo "env XXX" | bash > result/b_33.out
echo "env XXX" | ../21sh > result/33.out
dotest b_33.out 33.out
echo "builtin env ajout var"
echo "env TEST=BBBB | grep TEST" | bash > result/b_34.out
echo "env TEST=BBBB | grep TEST" | ../21sh > result/34.out
dotest b_34.out 34.out
echo "builtin env ajout var start binary"
echo "env TEST=BBBB ls" | bash > result/b_35.out
echo "env TEST=BBBB ls" | ../21sh > result/35.out
dotest b_35.out 35.out
echo "builtin env ajout var start binary"
echo "env TEST=BBBB ls" | bash > result/b_36.out
echo "env TEST=BBBB ls" | ../21sh > result/36.out
dotest b_36.out 36.out
#######################################################

##################### TEST NUM 12 #####################
echo " --- > TEST setenv && unsetenv < ---"
echo "builtin setenv test simple"
echo "setenv TEST abcd ; env" | env ROUGE= CYAN= VERT= JAUNE= BLEU= ../21sh
echo "${ROUGE}plz check if the env var TEST is present with value = abcd and press key to continue${RESETCOLOR}"
read -n1 -s
echo "builtin setenv test simple 2"
echo "setenv TEST ; env" | env ROUGE= CYAN= VERT= JAUNE= BLEU= ../21sh
echo "${ROUGE}plz check if the env var TEST is present with value empty and press key to continue${RESETCOLOR}"
read -n1 -s
echo "builtin setenv test simple error"
echo "setenv TEST OOOO AAAA" | env ROUGE= CYAN= VERT= JAUNE= BLEU= ../21sh
echo "${ROUGE}plz check the error message (expected "Too many arguments" and press key to continue${RESETCOLOR}"
read -n1 -s
echo "builtin setenv test simple 3"
echo "setenv TEST oooo ; env | grep TEST ; setenv TEST bbbb ; env | grep TEST" | env ROUGE= CYAN= VERT= JAUNE= BLEU= ../21sh
echo "${ROUGE}plz check if the env var TEST is present with value first value ooo and second value bbbb and press key to continue${RESETCOLOR}"
read -n1 -s
echo "builtin setenv test simple 4"
echo "setenv env ROUGE= CYAN= VERT= JAUNE= BLEU= ../21sh"
echo "${ROUGE}plz check if the setenv with no argument print the current env and press key to continue${RESETCOLOR}"
read -n1 -s
echo "builtin unsetenv test simple 1"
echo "setenv TEST oooo ; env; unsetenv TEST ; env" | env ROUGE= CYAN= VERT= JAUNE= BLEU= ../21sh
echo "${ROUGE}plz check if the env var TEST is present with value first value ooo and secondly if it has been removed and press key to continue${RESETCOLOR}"
read -n1 -s
echo "builtin unsetenv test simple 2 two unsetenv"
echo "setenv TEST1 oooo ; setenv TEST2 bbbb ; env; unsetenv TEST1 TEST2 ; env" | env ROUGE= CYAN= VERT= JAUNE= BLEU= ../21sh
echo "${ROUGE}plz check if the env var TEST1 and TEST2 are present secondly if they hav been removed and press key to continue${RESETCOLOR}"
read -n1 -s
echo "builtin unsetenv test simple error"
echo "unsetenv" | env ROUGE= CYAN= VERT= JAUNE= BLEU= ../21sh
echo "${ROUGE}plz check the error message (expected "Too few arguments" and press key to continue${RESETCOLOR}"
read -n1 -s
#######################################################
