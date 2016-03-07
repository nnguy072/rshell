#!/bin/sh
cd ..
make 
cd bin
./rshell << EOF
(echo hello && echo hi) || (ls -a; exit)
ls; echo hello || (echo hi && echo within parentheses)
ls || purposelyIncorrect || (echo hi; exit)
ls; (echo hi(echo hello && ls))
exit
EOF
