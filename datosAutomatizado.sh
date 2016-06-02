#!/bin/bash

IFS=$'\n'

num=0

echo

if [[ !  -d datFiles  ]];
then
	echo " ---------------------------------------"
	echo " -> No hay carpeta datFiles, creando. <-"
	echo " ---------------------------------------"

	mkdir datFiles
fi

echo 

for inst in $(ls instances/*);
do
	inst_name=$(echo $inst | sed "s/.*\/\(.*\)\..*/\1/")
	echo "  #################################################"
	echo " #"
	echo " # $num: Usando instancia $inst_name "
	echo " #" 

	for algo in {1..5};
	do
		echo " #  * Algorithm $algo:"
		dat_file=$(echo "datFiles/data_${inst_name}_Algoritmo-${algo}_$(date +%s).dat")
		echo " #     dat file -> $dat_file"
		./main_auto $inst $algo > $dat_file
	done

	echo "  #"
	echo "  #################################################"
	echo
	num=$((num + 1))
done

echo " ---------------------------------------- "
echo " -  Se han usado todas las instancias.  - "
echo " -            -> Saliendo <-            - "
echo " ---------------------------------------- "
