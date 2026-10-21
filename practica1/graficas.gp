set terminal pngcairo size 900,600
set encoding utf8
set grid
set key top left

ins = "exercise5output.txt"
bub = "exercise5boutput.txt"

# Columnas: 1 N, 2 n_elems, 3 time, 4 average_ob, 5 min_ob, 6 max_ob

# 1 Tiempos medios de CPU de los dos algoritmos
set output "tiempos.png"
set title "Tiempo medio de CPU en función del tamaño"
set xlabel "Tamaño de la permutación N (elementos)"
set ylabel "Tiempo medio de CPU (s)"
plot ins using 1:3 with linespoints title "InsertSort", \
     bub using 1:3 with linespoints title "BubbleSort"

# Escala común para las gráficas de OB
set yrange [0:5.5e7]
set xlabel "Tamaño de la permutación N (elementos)"
set ylabel "Número de ejecuciones de la OB"

# 2 OB de InsertSort
set output "ob_insertsort.png"
set title "InsertSort: ejecuciones de la OB"
plot ins using 1:4 with linespoints title "Medio", \
     ins using 1:5 with linespoints title "Mínimo", \
     ins using 1:6 with linespoints title "Máximo"

# 3 OB de BubbleSort
set output "ob_bubblesort.png"
set title "BubbleSort: ejecuciones de la OB"
plot bub using 1:4 with linespoints title "Medio", \
     bub using 1:5 with linespoints title "Mínimo", \
     bub using 1:6 with linespoints title "Máximo"

     