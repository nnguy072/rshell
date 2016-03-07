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
./rshell << EOF
test -e /home/csmajs/rho003/rshell; exit
EOF
./rshell << EOF
test -e /home/csmajs/rho003/rshell || exit
EOF
./rshell << EOF
test -e /home/csmajs/rho003/NotReal || exit
EOF
./rsehll << EOF
test -e /home/csmajs/rho003/rshell/src && exit
EOF
./rsehll << EOF
exit && test -e /home/csmajs/rho003/rshell/src
EOF

