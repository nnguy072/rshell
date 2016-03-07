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
#test -e /home/csmajs/rho003/rshell
echo hello; #test -e /home/csmajs/rho03/rshell
#test -e /home/csmajs/rho003/rshell/src/Parser.cpp && echo hello
test -e /home/csmajs/rho003/rshell; #echo testing
exit
EOF
