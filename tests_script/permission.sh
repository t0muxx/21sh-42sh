#/bin/sh

echo "---------- TESTING PERMISSIONS ----------"
dotest "cat unknow"
dotest "mkdir dir_noright ; touch file_noright ; chmod 000 dir_noright ; cat file_noright"
dotest "mkdir right ; cat right"
dotest "touch no_right ; chmod 000 no_right ; cat no_right"
dotest "mkdir dir ; touch no_right ; chmod 000 dir/no_right ; ls -la >> dir/no_right"
dotest "chmod 777 dir_noright ; rm -rf dir_noright"
