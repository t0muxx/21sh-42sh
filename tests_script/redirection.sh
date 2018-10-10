#/bin/bash

echo "----------- TESTING REDIRECTION ----------"

dotest "> toto ; cat toto"
dotest "file >"
dotest "echo test > toto ; cat toto" 
dotest "file >>"
dotest "echo toto >> tmp ; cat tmp" 
dotest "file <"
dotest "echo test > file ; cat < file" | ../21sh > result/6.out
dotest "echo foo > out; echo bar >> out; cat out"
dotest "echo foo > out2; echo bar >> out2; echo overwrite > out2; cat out2;"
dotest "echo text | wc > out.txt || nothing | wc > out.txt;cat out.txt"
dotest "test ; lss -la | wc > out.txt || ls | wc > out.txt && cat out.txt"
dotest "echo test; touchc a && touch b ; ls -la | wc > out.txt || ls | wc > out.txt && cat out.txt"
dotest "echo toto && ls | wc"
dotest "echo toto || ls | wc"
dotest "unknow toto || ls | wc > out"
dotest "echo toto ; ls | wc"
dotest "lsls 2> file ; cat file"
dotest "echo Error 1>&2 > file ; cat file"
dotest "ls 1>&- ; echo test"
dotest "ls >&- ; echo test"
dotest "lss 2>&-"
dotest "lss 2>&- && echo toto"
dotest "lss 2>&- || echo toto"
dotest "echo foo > output; echo bar > output2; cat > output > output3 < output2; cat output3"

echo "../../../../../../../../../../bin/ls /" | bash > bash_out/bash.out
echo "../../../../../../../../../../bin/ls /" | ../../21sh > 21sh_out/21sh.out
quickdiff bash_out/bash.out 21sh_out/21sh.out "../../../../../../../../../bin/ls /"
echo "unset PATH ; ls -la /" | bash > bash_out/bash.out
echo "unsetenv PATH ; ls -la /" | ../../21sh > 21sh_out/21sh.out
quickdiff bash_out/bash.out 21sh_out/21sh.out "unsetenv PATH ; ls -la /"
echo "unset PATH ; /bin/ls -la /" | bash > bash_out/bash.out
echo "unsetenv PATH ; /bin/ls -la /" | ../../21sh > 21sh_out/21sh.out
quickdiff bash_out/bash.out 21sh_out/21sh.out "unsetenv PATH ; /bin/ls -la /"
echo "unset PATH ; ../../../../../../../../../bin/ls -la /" | bash > bash_out/bash.out
echo "unsetenv PATH ; ../../../../../../../../../bin/ls -la /" | ../../21sh > 21sh_out/21sh.out
quickdiff bash_out/bash.out 21sh_out/21sh.out "unsetenv PATH ; ../../../../../../../../../bin/ls -la /"
cp /bin/ls $PWD/
echo "./ls -la /" | bash > bash_out/bash.out
echo "./ls -la /" | ../../21sh > 21sh_out/21sh.out
rm ls
quickdiff bash_out/bash.out 21sh_out/21sh.out "./ls -la /"

