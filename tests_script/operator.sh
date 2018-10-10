#!/bin/sh

echo " ------- TESTING OPERATORS -------"

dotest "echo qwertyuiop[] | wc"
dotest "ls | cat | wc -l"
dotest "cat | ls -la | grep 'result'"
dotest "cat | ls -la | grep 'result' | wc | wc -l"
echo "${CYAN}TEST DES PIPES ASYNCHRONE${RESETCOLOR}"
echo "Wait few seconds"
echo "sleep 4 && echo "ASYNCHRONOUS PIPE WORKING WELL"" | "../.././21sh"
dotest "echo qwertyuiop[] ; wc"
dotest "echo qwertyuiop[] ; wc ; echo oooooo"
dotest "echo qwertyuiop[] ; wc ; cat ; wc"
dotest "echo qwertyuiop[] || wc"
dotest "echoo qwertyuiop[] || wc"
dotest "echo qwertyuiop[] && wc"
dotest "echoo qwertyuiop[] && wc"
