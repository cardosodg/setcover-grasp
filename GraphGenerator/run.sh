#!\bin\bash

g++ gerador.cpp -o gerador -O2

rm -r input

mkdir input

./gerador 1 config.txt

rm gerador

mv instBFS_* input

