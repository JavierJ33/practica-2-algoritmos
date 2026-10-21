set term png size 800,500
set output "histograma.png"
set title "Histograma de frecuencias"
set xlabel "Numero"
set ylabel "Frecuencia"
set yrange [0:12000]
set xrange [0:11]
plot "Datos.txt" title "Frecuencia" with boxes, 10000 title "Media"