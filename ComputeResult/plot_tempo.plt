set term postscript eps enhanced color
#set term jpeg

set output "Grafico_Tempo.eps"
#set output "Grafico_Tempo.jpeg"

set grid
#set log

#set yrange [-10:]
#set xrange [150:]

set xlabel "Tamanho da rede."
set ylabel "Tempo (s)."

plot 'GREED.txt' using 1:3 title 'GREED' with linespoints lt 1 lw 2, \
     'LS.txt' using 1:3 title 'LS' with linespoints lt 0 lw 2, \
     'GRASP.txt' using 1:3 title 'GRASP' with linespoints lw 2
