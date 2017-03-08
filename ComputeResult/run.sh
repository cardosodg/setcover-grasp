#!/bin/bash

mkdir $1

g++ media.cpp -o media
g++ TabelaGrafico.cpp -o tabelagrafico

./media execGuloso.txt GREED.txt

./media execBl.txt LS.txt

./media execGrasp.txt GRASP.txt

./tabelagrafico

mv *.txt *.eps $1

rm media tabelagrafico
