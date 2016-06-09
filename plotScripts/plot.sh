#!/bin/bash

plot() {
cat << _end_ | gnuplot
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

currentBest_vs_BestOverall() {
#Extract file name and algorithm
for i in $(ls ../datFiles/*);
do
	file_name=$(echo $i | sed "s/.*data_\(.*\)_Algo.*/\1/")
	algorithm=$(echo $i | sed "s/.*data.*\(Algo.*\)_.*/\1/")
	exec_time=$(echo $i | sed "s/.*\([0-9]\{10,\}\)\.dat/\1/")
	echo " * Ploting file $file_name with algorithm $algorithm ($exec_time)"
	graph_name="../graphics/graphic_currentBest_vs_bestOverall-${file_name}-${algorithm}-${exec_time}.png"
	echo "    -> Plotting to $graph_name"
	echo
cat << _end_ | gnuplot
set terminal png giant font arial 12 size 800,600 
set key outside
set output "$graph_name"

plot for [col=2:3] '$i' using col smooth csplines title columnheader

_end_

#Por si lo clava a la primera y no hay suficientes datos para hacer un linea
if [[ $? -ne 0 ]];then
cat << _end_ | gnuplot
set terminal png giant font arial 12 size 800,600
set key outside
set output "$graph_name"

plot for [col=2:3] '$i' using col w p title columnheader

_end_
fi

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
set key outside
set output "$graph_name"

plot for [col=2:3] '$i' using col smooth csplines title columnheader

_end_
done
}

bestOfEach() {
cat << _end_ | gnuplot
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
	
	currentBest_vs_BestOverall

	#for i in $(ls ../datFiles/*);
	#do
	#	file_name=$(echo $i | sed "s/.*data_\(.*\)_Algo.*/\1/")
	#	echo " * The file name is $file_name"

	#	algorithm=$(echo $i | sed "s/.*data.*\(Algo.*\)_.*/\1/")
	#	#algorithm=$(echo $i | sed "s/.*data_.*_\(Algo.*\)_.*/ * algo -> \1/")
	#	echo "   The algorithm used with this file is -> $algorithm"
	#	echo
	#done

}

main "$@"
