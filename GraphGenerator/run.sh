#!\bin\bash

g++ gerador.cpp -o gerador -O2

rm -r input

mkdir input

./gerador 1 config.txt 1

python shortest_paths.py

rm gerador

mv instGraph_* input

