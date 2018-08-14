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

##################### TEST NUM 1 ######################
#######################################################

##################### TEST NUM 1 ######################
echo " --- > TEST BASIQUE 1 < ---"
echo "ls" | bash > result/b_1.out
echo "ls" | ../21sh > result/1.out
echo "ls -la" | bash > result/b_2.out
echo "ls -la" | ../21sh > result/2.out
echo "ls -l -a" | bash > result/b_3.out
echo "ls -l -a" | ../21sh > result/3.out
echo "lss" | bash 2> result/b_4.out
echo "lss" | ../21sh 2> result/4.out
dotest b_1.out 1.out
dotest b_2.out 2.out
dotest b_3.out 3.out
dotest b_4.out 4.out
#######################################################

##################### TEST NUM 2 ######################
echo " ---> TEST BASIQUE 2 < ---"
echo "redir >"
echo "ls > result/b_5.out" | bash 
echo "ls > result/5.out" | ../21sh 
dotest b_5.out 5.out
echo "redir >>"
echo "ls -la >> result/b_5.out" | bash 
echo "ls -la >> result/5.out" | ../21sh 
dotest b_5.out 5.out
echo "redir <"
echo "cat < result/b_5.out" | bash > result/b_6.out
echo "cat < result/5.out" | ../21sh > result/6.out
dotest b_6.out 6.out
#######################################################

##################### TEST NUM 3 ######################
echo " ---> TEST BASIQUE 3 < ---"
echo "pipe simple (1)"
echo "echo qwertyuiop[] | wc" | bash > result/b_7.out
echo "echo qwertyuiop[] | wc" | ../21sh > result/7.out
dotest b_7.out 7.out
echo "pipe simple (2)"
echo "ls | cat | wc -l" | bash > result/b_8.out
echo "ls | cat | wc -l" | ../21sh > result/8.out
dotest b_8.out 8.out
echo "pipe simple (3)"
echo "cat | ls -la | grep 'result'" | bash > result/b_9.out
echo "cat | ls -la | grep 'result'" | ../21sh > result/9.out
dotest b_9.out 9.out
echo "pipe simple (4)"
echo "cat | ls -la | grep 'result' | wc | wc -l" | bash > result/b_10.out
echo "cat | ls -la | grep 'result' | wc | wc -l" | ../21sh > result/10.out
dotest b_10.out 10.out
echo "${ROUGE}TEST DES PIPES ASYNCHRONE${RESETCOLOR}"
echo "Si 'OK21SH' apparait et le script pause 10sec les pipes asynchrone fonctionne"
echo "sleep 10 | echo "OK21sh"" | ../21sh
#######################################################

##################### TEST NUM 4 ######################
echo " ---> TEST BASIQUE 4 < ---"
echo "semilicon simple (1)"
echo "echo qwertyuiop[] ; wc" | bash > result/b_11.out
echo "echo qwertyuiop[] ; wc" | ../21sh > result/11.out
dotest b_11.out 11.out
echo "semilicon simple (2)"
echo "echo qwertyuiop[] ; wc ; echo oooooo" | bash > result/b_12.out
echo "echo qwertyuiop[] ; wc ; echo oooooo" | ../21sh > result/12.out
dotest b_12.out 12.out
echo "semilicon simple (3)"
echo "echo qwertyuiop[] ; wc ; cat ; wc" | bash > result/b_13.out
echo "echo qwertyuiop[] ; wc ; cat ; wc" | ../21sh > result/13.out
dotest b_13.out 13.out
#######################################################

##################### TEST NUM 5 ######################
echo " ---> TEST BASIQUE 5 < ---"
echo "|| simple (1)"
echo "echo qwertyuiop[] || wc" | bash > result/b_14.out
echo "echo qwertyuiop[] || wc" | ../21sh > result/14.out
dotest b_14.out 14.out
echo "|| simple ko (1)"
echo "echoo qwertyuiop[] || wc" | bash > result/b_15.out
echo "echoo qwertyuiop[] || wc" | ../21sh > result/15.out
dotest b_15.out 15.out
#######################################################

##################### TEST NUM 6 ######################
echo " ---> TEST BASIQUE 6 < ---"
echo "&& simple (1)"
echo "echo qwertyuiop[] && wc" | bash > result/b_16.out
echo "echo qwertyuiop[] && wc" | ../21sh > result/16.out
dotest b_16.out 16.out
echo "&& simple ko (1)"
echo "echoo qwertyuiop[] && wc" | bash > result/b_17.out
echo "echoo qwertyuiop[] && wc" | ../21sh > result/17.out
dotest b_17.out 17.out
#######################################################
