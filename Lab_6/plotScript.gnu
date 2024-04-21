set terminal png
set output 'plot.png'
plot "dataOutput.txt" u 1:2 w l