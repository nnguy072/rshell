#!/bin/sh
cd ..
make 
cd bin
./rshell << EOF
test -e /home/csmajs/rho003/rshell
test -e /home/csmajs/rho003/rshell/src/Parser.cpp
[ -e /home/csmajs/rho003/rshell ]
[ -e /home/csmajs/rho003/rshell/src/Parser.cpp ]
test -e /home/csmajs/rho003/rshell && echo "hi"
[ -e /home/csmajs/rho003/rshell ] && echo "hi"
test -e /home/csmajs/rho003/rshell/src/Parser.cpp && echo "hi"
[ -e /home/csmajs/rho003/rshell/src/Parser.cpp ] && echo "hi"
exit
EOF

