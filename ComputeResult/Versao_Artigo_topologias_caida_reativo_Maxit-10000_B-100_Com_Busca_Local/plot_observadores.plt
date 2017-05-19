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

plot 'SMV.txt' using 1:2 title 'SMV' with linespoints lt 16 lw 3 dt 3, \
     'GRASP.txt' using 1:2 title 'GRASP' with linespoints lt 24 lw 3 dt 1

