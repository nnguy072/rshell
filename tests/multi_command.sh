#!/bin/sh
cd ..
make
cd bin
./rshell << EOF
ls -a; echo hi
ls; echo hello world
ls; echo hello || echo world
ls || echo one round
echo warmup || ls -a;
echo GGEZ; ls
l || echo first one failed
s || echo its not laggy anymore
echo run this && echo run that
ls && ls -a
l && echo should not echo
exit
EOF
