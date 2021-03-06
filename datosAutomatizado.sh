#!/bin/bash

IFS=$'\n'

num=0

echo

if [[ !  -d datFiles ]];
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

	for algo in {1..6};
	do
		echo " #  * Algoritmo $algo:"
		dat_file=$(echo "datFiles/data_${inst_name}_Algoritmo-${algo}_$(date +%s).dat")
		#Asi seria mas intuitivo al leer el nombre (not really)
		#dat_file=$(echo "datFiles/data_${inst_name}-Algoritmo_${algo}-$(date +%s).dat")
		echo " #     dat file -> $dat_file"
		echo "iter \"mejor iteracion actual\" \"mejor encontrado\"" >> $dat_file
		nice -n -15 ./main_auto $inst $algo >> $dat_file
	done

	echo " #"
	echo "  #################################################"
	echo
	num=$((num + 1))
done

echo " ---------------------------------------- "
echo " -  Se han usado todas las instancias.  - "
echo " -            -> Saliendo <-            - "
echo " ---------------------------------------- "
