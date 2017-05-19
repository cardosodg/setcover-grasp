set term postscript eps enhanced color
#set term jpeg

set output "Grafico_Observadores.eps"
#set output "Grafico_Observadores.jpeg"

set grid
#set log

set key left

#set yrange [-10:]
#set xrange [150:]

set xlabel "Tamanho da rede."
set ylabel "Observadores."

plot 'SMV.txt' using 1:2 title 'SMV' with linespoints lt 16 lw 3 dt 3, \
     'SMV-A.txt' using 1:2 title 'SMV-A' with linespoints lt 8 lw 3 dt 2 pt 2, \
     'BL.txt' using 1:2 title 'BL' with linespoints lt 32 lw 3 dt 1 pt 6 ps 1.5, \
     'GRASP.txt' using 1:2 title 'GRASP' with linespoints lt 24 lw 3 dt 4

