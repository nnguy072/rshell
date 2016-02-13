#!/bin/sh
cd ..
make
cd bin
./rshell << EOF
ls; exit
EOF
./rshell << EOF
ls -a; exit
EOF
./rshell << EOF
echo hi; exit
EOF
./rshell << EOF
ls; echo 2 commands; exit
EOF
