set termoption noenhanced
set terminal pngcairo size 1200,800
set grid
set key top left
set xlabel "Tamano del array (N)"

# Comparacion de tiempos medios
set output "comparacion_tiempo.png"
set title "MergeSort vs QuickSort_mean - Tiempo medio de CPU"
set ylabel "Tiempo medio de CPU (segundos)"

plot "mergesort.dat" using 1:3 with linespoints title "MergeSort", \
     "quicksort_mean.log" using 1:3 with linespoints title "QuickSort_mean"

# Comparacion de comparaciones medias
set output "comparacion_ob.png"
set title "MergeSort vs QuickSort_mean - Comparaciones medias"
set ylabel "Comparaciones (OB)"

plot "mergesort.dat" using 1:4 with linespoints title "MergeSort", \
     "quicksort_mean.log" using 1:4 with linespoints title "QuickSort_mean"

set output
