#/bin/bash

dotest "mkdir test && cd test ; touch a && touch b ; ls -la ; cd .. ; rm -rf test"
dotest "cd testd"
dotest "mkdir -p test/a/b/c/d/e/f ; cd test/a/b/c/d/e/f ; pwd ; rm -rf test"
dotest "cd ; pwd ; cd - ; pwd"
#echo "unset HOME ; cd" | bash > result/b_31.out
#echo "unsetenv HOME ; cd" | ../21sh > result/31.out
dotest "env TEST=BBBB | grep TEST"
dotest "env TEST=BBBB echo"
dotest "env TEST=BBBB echo | grep TEST"
dotest "env TEST=BBBB lss"
dotest "env -i env"
dotest "env -i TEST=AAAA env"
dotest "env -i TEST=EEEE TEST2=AAAAA env"
dotest "env TEST=aaaa -i ls"
dotest "cd ../../../tests_script ; env | grep --color=never ^PWD"
dotest "cd ../../../tests_script//// ; env | grep --color=never ^PWD"
dotest "cd ../../../tests_script/output ; env | grep --color=never ^PWD"
dotest "cd ../../../../../../../../../../../../../ ; env | grep --color=never ^PWD"
dotest "cd unknow_dir ; env | grep  --color=never ^PWD"
dotest "cd /Users ; env | grep  --color=never ^PWD"
dotest "cd /./Users ; env | grep  --color=never ^PWD"
dotest "cd -P /tmp/ ; pwd"
dotest "cd /tmp; mkdir parent; cd parent; touch file; rm -rf ../parent; cd ..; env | grep --color=never ^PWD"
echo "$INDEX setenv TEST abcd ; env | grep TEST"
echo "setenv TEST abcd ; env | grep TEST" | env ROUGE= CYAN= VERT= JAUNE= BLEU= ../../21sh
echo "${CYAN}plz check if the env var TEST is present with value = abcd and press key to continue${RESETCOLOR}"
read -n1 -s
echo "$INDEX setenv TEST ; env | grep TEST"
echo "setenv TEST ; env | grep TEST" | env ROUGE= CYAN= VERT= JAUNE= BLEU= ../../21sh
echo "${CYAN}plz check if the env var TEST is present with value empty and press key to continue${RESETCOLOR}"
read -n1 -s
echo "$INDEX setenv TEST OOOO AAAA"
echo "setenv TEST OOOO AAAA" | env ROUGE= CYAN= VERT= JAUNE= BLEU= ../../21sh
echo "${CYAN}plz check the error message (expected "Too many arguments" and press key to continue${RESETCOLOR}"
read -n1 -s
echo "$INDEX setenv TEST oooo ; env | grep TEST ; setenv TEST bbbb ; env | grep TEST"
echo "setenv TEST oooo ; env | grep TEST ; setenv TEST bbbb ; env | grep TEST" | env ROUGE= CYAN= VERT= JAUNE= BLEU= ../../21sh
echo "${CYAN}plz check if the env var TEST is present with value first value ooo and second value bbbb and press key to continue${RESETCOLOR}"
read -n1 -s
echo "$INDEX setenv"
echo "setenv" | env ROUGE= CYAN= VERT= JAUNE= BLEU= ../../21sh
echo "${CYAN}plz check if the setenv with no argument print the current env and press key to continue${RESETCOLOR}"
read -n1 -s
echo "$INDEX setenv TEST oooo ; env | grep TEST ; unsetenv TEST ; echo second : ;  env | grep TEST"
echo "setenv TEST oooo ; env | grep TEST ; unsetenv TEST ; echo second : ;  env | grep TEST" | env ROUGE= CYAN= VERT= JAUNE= BLEU= ../../21sh
echo "${CYAN}plz check if the env var TEST is present with value first value ooo and secondly if it has been removed and press key to continue${RESETCOLOR}"
read -n1 -s
echo "$INDEX setenv TEST1 oooo ; setenv TEST2 bbbb ; env | grep TEST ; echo second ; unsetenv TEST1 TEST2 ; env | grep TEST"
echo "setenv TEST1 oooo ; setenv TEST2 bbbb ; env | grep TEST ; echo second ; unsetenv TEST1 TEST2 ; env | grep TEST" | env ROUGE= CYAN= VERT= JAUNE= BLEU= ../../21sh
echo "${CYAN}plz check if the env var TEST1 and TEST2 are present secondly if they hav been removed and press key to continue${RESETCOLOR}"
read -n1 -s
echo "$INDEX unsetenv"
echo "unsetenv" | env ROUGE= CYAN= VERT= JAUNE= BLEU= ../../21sh
echo "${CYAN}plz check the error message (expected "Too few arguments" and press key to continue${RESETCOLOR}"
read -n1 -s
