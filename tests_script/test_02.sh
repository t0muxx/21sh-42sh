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
	rm result/$1 result/$2
	echo " =========================== "
	read -n1 -s

}

##################### TEST NUM 1 ######################
#######################################################

##################### TEST NUM 7 ######################
rm -rf test
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

##################### TEST NUM 10 #####################
echo " --- > TEST 10 < ---"
echo "redir hard "
mkdir tmp
touch tmp/no_right
touch tmp/right
ls -la > tmp/no_right
ls -la > tmp/right
echo "file doesnt exist "
echo "cat < tmpxx" | bash > result/b_21.out
echo "cat < tmpxx" | ../21sh > result/21.out
dotest b_21.out 21.out
echo "no right on file "
chmod 000 tmp/no_right
echo "cat < tmp/no_right" | bash > result/b_22.out
echo "cat < tmp/no_right" | ../21sh > result/22.out
dotest b_22.out 22.out
echo "file exist "
echo "cat < tmp/right" | bash > result/b_23.out
echo "cat < tmp/right" | ../21sh > result/23.out
dotest b_23.out 23.out
echo "no right on file > "
chmod 000 tmp/no_right
echo "ls -la > tmp/no_right" | bash > result/b_23.out
echo "ls -la > tmp/no_right" | ../21sh > result/23.out
dotest b_23.out 23.out
echo "no right on file >> "
chmod 000 tmp/no_right
echo "ls -la >> tmp/no_right" | bash > result/b_24.out
echo "ls -la >> tmp/no_right" | ../21sh > result/24.out
dotest b_24.out 24.out
rm -rf tmp
echo "multiple redir "
mkdir tmp_b
mkdir tmp
echo "ceci est un test" > tmp_b/tmp4
echo "ceci est un test" > tmp/tmp4
echo "cat > tmp_b/tmp > tmp_b/tmp2 > tmp_b/tmp3 < tmp_b/tmp4" | bash
echo "cat > tmp/tmp > tmp/tmp2 > tmp/tmp3 < tmp/tmp4" | ../21sh
ls -l tmp_b/ > result/b_25.out
ls -l tmp/ >  result/25.out
dotest b_25.out 25.out
echo "cat tmp_b/tmp ; cat tmp_b/tmp2 ; cat tmp_b/tmp3 ; cat tmp_b/tmp4" | bash > result/b_26.out
echo "cat tmp/tmp ; cat tmp/tmp2 ; cat tmp/tmp3 ; cat tmp/tmp4" | ../21sh > result/26.out
dotest b_26.out 26.out
rm -rf tmp_b
rm -rf tmp
#######################################################

#######################################################
echo " --- > TEST AGGREGATOR < ---"
echo "agregator"
echo "Redirecting stderr"
echo "lsls 2> result/b_out" | bash
echo "lsls 2> result/out" | ../21sh
dotest b_out out
echo "lsls 2> result/b_out" | bash > result/b_out1
echo "lsls 2> result/out" | ../21sh > result/out1
dotest b_out1 out1
echo "Redirecting stdout to stderr"
echo "echo "Error" 1>&2" | bash 2> result/b_out
echo "echo "Error" 1>&2" | ../21sh 2> result/out
dotest b_out out
echo "Closing Stdout"
echo "ls 1>&- ; ls" | bash > result/b_out
echo "ls 1>&- ; ls" | ../21sh > result/out
dotest b_out out
echo "ls >&- ; ls" | bash > result/b_out
echo "ls >&- ; ls" | ../21sh > result/out
dotest b_out out
echo "closing stderr"
echo "lss 2>&- " | bash 2> result/b_out
echo "lss 2>&- " | ../21sh 2> result/out
dotest b_out out
echo "lss 2>&- && ls" | bash > result/b_out
echo "lss 2>&- && ls" | ../21sh > result/out
dotest b_out out
echo "lss 2>&- || ls" | bash > result/b_out
echo "lss 2>&- || ls" | ../21sh > result/out
dotest b_out out
######################################################

#######################################################
echo " --- > TEST EXEC < ---"
echo "exec hard"
echo "../../../../../../../../../bin/ls /" | bash > result/b_out
echo "../../../../../../../../../bin/ls /" | ../21sh > result/out
dotest b_out out
echo "exec without PATH"
echo "unset PATH ; ls -la /" | bash > result/b_out
echo "unsetenv PATH ; ls -la /" | ../21sh > result/out666
dotest b_out out666
echo "exec without PATH var but full path precised"
echo "unset PATH ; /bin/ls -la /" | bash > result/b_out
echo "unsetenv PATH ; /bin/ls -la /" | ../21sh > result/out
dotest b_out out
echo "exec without PATH var but full path precised (2)"
echo "unset PATH ; ../../../../../../../../../bin/ls -la /" | bash > result/b_out
echo "unsetenv PATH ; ../../../../../../../../../bin/ls -la /" | ../21sh > result/out
dotest b_out out
echo "exec local bin"
cp /bin/ls $PWD/
echo "./ls -la /" | bash > result/b_out
echo "./ls -la /" | ../21sh > result/out
rm ls
dotest b_out out
#######################################################
