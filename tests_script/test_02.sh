#!/usr/bin/bash
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

##################### TEST NUM 1 ######################
#######################################################

##################### TEST NUM 7 ######################
echo " --- > TEST 7 < ---"
echo "combinaison of ; | || && > "
echo "mkdir test && cd test ; touch a && touch b ; ls -la | wc > out.txt || ls | wc > out.txt && cd .. ; pwd ; cat test/out.txt ; rm -rf test" | bash > result/b_18.out
echo "mkdir test && cd test ; touch a && touch b ; ls -la | wc > out.txt || ls | wc > out.txt && cd .. ; pwd ; cat test/out.txt ; rm -rf test" | ../21sh > result/18.out
dotest b_18.out 18.out
#######################################################

##################### TEST NUM 8 ######################
echo " --- > TEST 8 < ---"
echo "combinaison of ; | || && > (2) "
echo "mkdir test && cd test ; touch a && touch b ; lss -la | wc > out.txt || ls | wc > out.txt && cat out.txt ; cd .. ; rm -rf test" | bash > result/b_19.out
echo "mkdir test && cd test ; touch a && touch b ; lss -la | wc > out.txt || ls | wc > out.txt && cat out.txt ; cd .. ; rm -rf test" | ../21sh > result/19.out
dotest b_19.out 19.out
#######################################################

##################### TEST NUM 9 ######################
echo " --- > TEST 9 < ---"
echo "combinaison of ; | || && > (3) "
echo "mkdir test && cd test ; touchc a && touch b ; ls -la | wc > out.txt || ls | wc > out.txt && cat out.txt ; cd .. ; rm -rf test" | bash > result/b_20.out
echo "mkdir test && cd test ; touchc a && touch b ; ls -la | wc > out.txt || ls | wc > out.txt && cat out.txt ; cd .. ; rm -rf test" | ../21sh > result/20.out
dotest b_20.out 20.out
#######################################################
