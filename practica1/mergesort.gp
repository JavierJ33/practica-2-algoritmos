
set terminal pngcairo size 1200,800
set grid
set key top left
set xlabel "Tamano del array (N)"

# Modelos teoricos
f(x) = a*x*log(x)/log(2.0)
g(x) = b*x*log(x)/log(2.0)

a = 1
b = 0.00000001

# Ajustes con datos experimentales
fit [100:1000] f(x) "mergesort.dat" using 1:4 via a
fit [100:1000] g(x) "mergesort.dat" using 1:3 via b

# Grafica de comparaciones
set output "mergesort_ob.png"
set title "MergeSort - Numero de comparaciones"
set ylabel "Comparaciones (OB)"

plot "mergesort.dat" using 1:4 with linespoints title "OB media", \
     "mergesort.dat" using 1:5 with linespoints title "OB minima", \
     "mergesort.dat" using 1:6 with linespoints title "OB maxima", \
     f(x) with lines linewidth 2 title "Ajuste N log2(N)"

# Grafica de tiempo
set output "mergesort_tiempo.png"
set title "MergeSort - Tiempo medio de CPU"
set ylabel "Tiempo medio de CPU (segundos)"

plot "mergesort.dat" using 1:3 with linespoints title "Tiempo medio", \
     g(x) with lines linewidth 2 title "Ajuste N log2(N)"

set output

print "Coeficiente OB (a) = ", a
print "Coeficiente tiempo (b) = ", b
