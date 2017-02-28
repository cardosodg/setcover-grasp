set term postscript eps enhanced color
#set term jpeg

set output "Grafico_Observadores.eps"
#set output "Grafico_Observadores.jpeg"

set grid
#set log

#set yrange [-10:]
#set xrange [150:]

set xlabel "Tamanho da rede."
set ylabel "Observadores."

plot 'GREED.txt' using 1:2 title 'GREED' with linespoints lt 1 lw 2, \
     'LS.txt' using 1:2 title 'LS' with linespoints lt 0 lw 2, \
     'GRASP.txt' using 1:2 title 'GRASP' with linespoints lw 2
