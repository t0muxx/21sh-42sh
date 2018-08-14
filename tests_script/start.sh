PATH_TO_21SH="../21sh"
CDIR=${PWD}
RESETCOLOR="$(tput sgr0)"
# Couleurs (gras)
ROUGE="$(tput bold ; tput setaf 1)"
VERT="$(tput bold ; tput setaf 2)"
JAUNE="$(tput bold ; tput setaf 3)"
BLEU="$(tput bold ; tput setaf 4)"
CYAN="$(tput bold ; tput setaf 6)"
PRINTDEBUG=1

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
	if [ -e result ]
	then
		rm -rf result
	fi
	mkdir result
}

echo "${VERT}#################################################${RESETCOLOR}"
echo "${VERT}#               21sh  tester                    #${RESETCOLOR}"
echo "${VERT}#                                               #${RESETCOLOR}"
echo "${VERT}#                                               #${RESETCOLOR}"
echo "${VERT}#                              by : tmaraval    #${RESETCOLOR}"
echo "${VERT}#                                               #${RESETCOLOR}"
echo "${VERT}#################################################${RESETCOLOR}"

initdir
./test_01_simple.sh
./test_02.sh
