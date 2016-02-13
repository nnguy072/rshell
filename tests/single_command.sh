#!/bin/sh
cd ..
make
cd bin
./rshell << EOF
ls
ls -a
echo Hello
echo Hello World
date
exit
EOF
