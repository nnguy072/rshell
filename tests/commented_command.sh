#!/bin/sh
cd ..
make
cd bin
./rshell << EOF
#testing comment
ls # testing comment
ls; echo hello #where is the segfault?
ls || echo hello world #is it here?
echo 5th test #hiasd
exit
EOF
