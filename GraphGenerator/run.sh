#!\bin\bash

g++ gerador.cpp -o gerador -O2

rm -r input

mkdir input

./gerador 1 config.txt 0

python shortest_paths.py

rm gerador

mv instGraph_* input

