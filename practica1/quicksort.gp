
set terminal pngcairo size 1200,800
set termoption noenhanced
set fit quiet
set grid
set key top left
set xlabel "Tamano del array (N)"

# Modelos para comparaciones
f_min(x) = a_min*x*log(x)/log(2.0)
f_mean(x) = a_mean*x*log(x)/log(2.0)
f_median(x) = a_median*x*log(x)/log(2.0)

# Modelos para tiempo
g_min(x) = b_min*x*log(x)/log(2.0)
g_mean(x) = b_mean*x*log(x)/log(2.0)
g_median(x) = b_median*x*log(x)/log(2.0)

# Valores iniciales
a_min = 1
a_mean = 1
a_median = 1

b_min = 0.00000001
b_mean = 0.00000001
b_median = 0.00000001

# Ajustes de comparaciones
fit [100:1000] f_min(x) "quicksort_min.log" using 1:4 via a_min
fit [100:1000] f_mean(x) "quicksort_mean.log" using 1:4 via a_mean
fit [100:1000] f_median(x) "quicksort_median.log" using 1:4 via a_median

# Ajustes de tiempo
fit [100:1000] g_min(x) "quicksort_min.log" using 1:3 via b_min
fit [100:1000] g_mean(x) "quicksort_mean.log" using 1:3 via b_mean
fit [100:1000] g_median(x) "quicksort_median.log" using 1:3 via b_median


# ==========================================
# GRAFICAS COMPARATIVAS DE LAS TRES VARIANTES
# ==========================================

# Grafica de comparaciones medias
set output "quicksort_ob.png"
set title "QuickSort - Comparaciones medias"
set ylabel "Comparaciones (OB)"

plot "quicksort_min.log" using 1:4 with linespoints title "QuickSort min", \
     "quicksort_mean.log" using 1:4 with linespoints title "QuickSort mean", \
     "quicksort_median.log" using 1:4 with linespoints title "QuickSort median", \
     f_min(x) with lines dashtype 2 title "Ajuste min", \
     f_mean(x) with lines dashtype 2 title "Ajuste mean", \
     f_median(x) with lines dashtype 2 title "Ajuste median"


# Grafica de tiempos medios
set output "quicksort_tiempo.png"
set title "QuickSort - Tiempo medio de CPU"
set ylabel "Tiempo medio de CPU (segundos)"

plot "quicksort_min.log" using 1:3 with linespoints title "QuickSort min", \
     "quicksort_mean.log" using 1:3 with linespoints title "QuickSort mean", \
     "quicksort_median.log" using 1:3 with linespoints title "QuickSort median", \
     g_min(x) with lines dashtype 2 title "Ajuste min", \
     g_mean(x) with lines dashtype 2 title "Ajuste mean", \
     g_median(x) with lines dashtype 2 title "Ajuste median"


# ==========================================
# GRAFICAS INDIVIDUALES DE QUICKSORT_MIN
# ==========================================

# Tiempo medio de CPU
set output "quicksort_min_tiempo.png"
set title "QuickSort_min - Tiempo medio de CPU"
set ylabel "Tiempo medio de CPU (segundos)"

plot "quicksort_min.log" using 1:3 with linespoints title "Tiempo medio", \
     g_min(x) with lines linewidth 2 title "Ajuste N log2(N)"


# Comparaciones
set output "quicksort_min_ob.png"
set title "QuickSort_min - Numero de comparaciones"
set ylabel "Comparaciones (OB)"

plot "quicksort_min.log" using 1:4 with linespoints title "OB media", \
     "quicksort_min.log" using 1:5 with linespoints title "OB minima", \
     "quicksort_min.log" using 1:6 with linespoints title "OB maxima", \
     f_min(x) with lines linewidth 2 title "Ajuste N log2(N)"


# ==========================================
# GRAFICAS INDIVIDUALES DE QUICKSORT_MEAN
# ==========================================

# Tiempo medio de CPU
set output "quicksort_mean_tiempo.png"
set title "QuickSort_mean - Tiempo medio de CPU"
set ylabel "Tiempo medio de CPU (segundos)"

plot "quicksort_mean.log" using 1:3 with linespoints title "Tiempo medio", \
     g_mean(x) with lines linewidth 2 title "Ajuste N log2(N)"


# Comparaciones
set output "quicksort_mean_ob.png"
set title "QuickSort_mean - Numero de comparaciones"
set ylabel "Comparaciones (OB)"

plot "quicksort_mean.log" using 1:4 with linespoints title "OB media", \
     "quicksort_mean.log" using 1:5 with linespoints title "OB minima", \
     "quicksort_mean.log" using 1:6 with linespoints title "OB maxima", \
     f_mean(x) with lines linewidth 2 title "Ajuste N log2(N)"


# ==========================================
# GRAFICAS INDIVIDUALES DE QUICKSORT_MEDIAN
# ==========================================

# Tiempo medio de CPU
set output "quicksort_median_tiempo.png"
set title "QuickSort_median - Tiempo medio de CPU"
set ylabel "Tiempo medio de CPU (segundos)"

plot "quicksort_median.log" using 1:3 with linespoints title "Tiempo medio", \
     g_median(x) with lines linewidth 2 title "Ajuste N log2(N)"


# Comparaciones
set output "quicksort_median_ob.png"
set title "QuickSort_median - Numero de comparaciones"
set ylabel "Comparaciones (OB)"

plot "quicksort_median.log" using 1:4 with linespoints title "OB media", \
     "quicksort_median.log" using 1:5 with linespoints title "OB minima", \
     "quicksort_median.log" using 1:6 with linespoints title "OB maxima", \
     f_median(x) with lines linewidth 2 title "Ajuste N log2(N)"


set output

# Mostrar los coeficientes finales
print "Coeficiente OB min = ", a_min
print "Coeficiente OB mean = ", a_mean
print "Coeficiente OB median = ", a_median

print "Coeficiente tiempo min = ", b_min
print "Coeficiente tiempo mean = ", b_mean
print "Coeficiente tiempo median = ", b_median
