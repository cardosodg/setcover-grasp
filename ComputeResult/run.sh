#!/bin/bash

mkdir $1

g++ media.cpp -o media
g++ TabelaGrafico.cpp -o tabelagrafico

#./media execGREED.txt GREED.txt

#./media execLS.txt LS.txt

#./media execGRASP.txt GRASP.txt

./tabelagrafico

mv *.txt *.eps $1

rm media tabelagrafico
