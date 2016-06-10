#!/bin/bash

currentBest_vs_bestOverall() {
#Extract file name and algorithm
for i in $(ls ../datFiles/*);
do
	file_name=$(echo $i | sed "s/.*data_\(.*\)_Algo.*/\1/")
	algorithm=$(echo $i | sed "s/.*data.*\(Algo.*\)_.*/\1/")
	exec_time=$(echo $i | sed "s/.*\([0-9]\{10,\}\)\.dat/\1/")
	echo " * Ploting file $file_name with algorithm $algorithm ($exec_time)"
	graph_name="../graphics/graphic_currentBest_vs_bestOverall-${file_name}-${algorithm}-${exec_time}"
	echo "    -> Plotting to $graph_name"
	lines=$(wc -l $i | grep -o "^ *[0-9]*" | tr -d "\n| ")
	echo "    -> Current file has $lines lines. "
	echo

	if [ $lines -lt 5  ]; then
		plot_line="plot for [col=2:3] '$i' using col w p title columnheader"
	elif [ $lines -lt 10 ];then
		#plot_line="plot for [col=2:3] '$i' using col w l title columnheader	"
		plot_line="plot '$i' using 1:2 w l lc rgb \"forest-green\" title columnheader, '$i' using 1:3 w l lc rgb \"midnight-blue\" title columnheader"
	elif [ $lines -lt 5000 ];then
		plot_line="plot '$i' using 1:2 w l lc rgb \"forest-green\" title columnheader, '$i' using 1:3 w l lc rgb \"midnight-blue\" title columnheader"
	elif [ $lines -lt 70000 ]; then
		plot_line="plot for [col=2:3] '$i' using col w l title columnheader"
	elif [ $lines -gt 100000  ];then
		plot_line="plot '$i' using 1:2 w l lc rgb \"forest-green\" title columnheader, '$i' using 1:3 w l lc rgb \"midnight-blue\" title columnheader
		set samples 10000
		set output \"${graph_name}_csplines.png\"
		plot for [col=2:3] '$i' using col smooth csplines title columnheader"
	else
		plot_line="plot for [col=2:3] '$i' using col smooth csplines title columnheader	"
	fi

cat << _end_ | gnuplot
set lt 1 lc rgb "forest-green" lw 1
set lt 2 lc rgb "midnight-blue" lw 2

set terminal png giant font arial 12 size 800,600 enhanced background rgb 'beige'
set xlabel "Iteraciones"
set ylabel "Fitness"
set key tmargin
set output "${graph_name}.png"
$plot_line
_end_
done
}

best_for_each_file() {
#Extract file name and algorithm
#Coger fichero de instancias y mirar todos algoritmos para ese fichero
for i in $(ls ../instances/*);
do
	file_name=$(echo $i | sed "s/.*data_\(.*\)_Algo.*/\1/")
	algorithm=$(echo $i | sed "s/.*data.*\(Algo.*\)-.*/\1/")
	exec_time=$(echo $i | sed "s/.*\([0-9]\{10,\}\)\.dat/\1/")
	#algorithm=$(echo $i | sed "s/.*data_.*_\(Algo.*\)_.*/ * algo -> \1/")
	echo " * Ploting file  $file_name with algorithm $algorithm ($exec_time)"
	graph_name="../graphics/graphic_currentBest_vs_BestOveral-${file_name}-${algorithm}-${exec_time}.png"
cat << _end_ | gnuplot
set terminal png giant font arial 12 size 800,600
set xlabel "Iteraciones"
set ylabel "Fitness"
set key right bottom
set output "$graph_name"

plot for [col=2:3] '$i' using col w p title columnheader
_end_
done
}

best_of_each() {
#Se haria de alguna manera asi, pero no se como
#https://stackoverflow.com/questions/11092608/gnuplot-plotting-data-from-multiple-input-files-in-a-single-graph
cat << _end_ | gnuplot
set terminal png giant font arial 12 size 800,600
set key outside
set output "$graph_name"
set terminal png giant font arial 12 size 800,600 
set xlabel "Fitness"
set ylabel "Weight"
set key right bottom

set output "../graphics/ComplexAsFuck-CurvesIIV.png"
plot "../datFiles/ben-weight_Best_EvenLines.txt" using 1:2 title "Best" w p pt 1, \
"../datFiles/weight.txt" using 1:2 t "Capacity" w l lt rgb "red", \
"../datFiles/ben-weight_Rand_OddLines.txt" using 1:2 title "Initial" w p pt 1
_end_
}

main() {
	IFS=$'\n'
	if [ ! -d ../graphics ]; then
		echo "creating graphics folder"
		mkdir ../graphics;
	fi
	
	currentBest_vs_bestOverall
}

main "$@"
