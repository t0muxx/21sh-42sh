#/bin/bash
PATH_TO_21SH="../21sh"
BIN_42SH="../.././21sh"
INDEX="1"
CDIR=${PWD}
RESETCOLOR="$(tput sgr0)"
# Couleurs (gras)
ROUGE="$(tput bold ; tput setaf 1)"
VERT="$(tput bold ; tput setaf 2)"
JAUNE="$(tput bold ; tput setaf 3)"
BLEU="$(tput bold ; tput setaf 4)"
CYAN="$(tput bold ; tput setaf 6)"
PRINTDEBUG=1
INDEX=1

export PATH_TO_21SH
export ROUGE
export VERT
export JAUNE
export BLEU
export CYAN
export RESETCOLOR
export PRINTDEBUG

initdir()
{
	if [ ! -e output ]
	then
		mkdir output
		mkdir output/21sh_out
		mkdir output/bash_out
	fi
}

cmpdiff()
{
	diff "$1" "$2" > diff.txt
	if [ $? -ne 0 ]; then
		echo "$INDEX${ROUGE}[KO]$3 ${RESETCOLOR}";
	else
		echo "$INDEX${VERT}[OK]$3 ${RESETCOLOR}"
	fi
}

printdebug()
{
	if [ $PRINTDEBUG -eq 1 ]
	then
		if [ -s diff.txt ]
		then
			echo "${ROUGE}********************* DIFF_$INDEX.TXT *************************${RESETCOLOR}"			
			cat diff.txt
			echo "${ROUGE}********************* DIFF_$INDEX.TXT *************************${RESETCOLOR}"
		fi
	fi
}

quickdiff()
{
	cmpdiff "$1" "$2" "$3"
	printdebug
	rm -rf bash_out/* 21sh_out/*
	INDEX=$((INDEX+1))
	read -n1 -s
}

dotest()
{
	cd bash_out
	echo "$1" | bash > "bash.out"
	cd ../21sh_out
	echo "$1" | "../../.././21sh" > "21sh.out"
	cd ..
	cmpdiff "bash_out/bash.out" "21sh_out/21sh.out" "$1"
	printdebug
	rm -rf bash_out/* 21sh_out/*
	INDEX=$((INDEX+1))
	read -n1 -s
}

echo "${VERT}#################################################${RESETCOLOR}"
echo "${VERT}#               21sh  tester                    #${RESETCOLOR}"
echo "${VERT}#                                               #${RESETCOLOR}"
echo "${VERT}#                                               #${RESETCOLOR}"
echo "${VERT}#                              by : tmaraval    #${RESETCOLOR}"
echo "${VERT}#                                               #${RESETCOLOR}"
echo "${VERT}#################################################${RESETCOLOR}"

initdir
cd output
. .././builtin.sh
. .././permission.sh
. .././redirection.sh
. .././operator.sh
cd ..
rm -rf output

