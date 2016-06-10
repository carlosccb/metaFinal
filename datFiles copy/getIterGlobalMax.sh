#file_name="data_CBS_k3_n100_m449_b90_1_Algoritmo-1_1465382574.dat"
#lines=$(wc -l data_CBS_k3_n100_m449_b90_1_Algoritmo-1_1465382574.dat | grep -o "^ *[0-9]*" | tr -d "\n| ")
#tail -n $((lines-1)) $file_name

#Mas facil
#for i in $(find . -maxdepth 1 -type d ! -path "./.*|.");do

getAlgoName() {
algo_name=""
case $1 in
	1)
	  algo_name="Busqueda_Aleatoria"
      ;; 
	2) 
	  algo_name="Busqueda_Local"
   	   ;;
	3)
	  algo_name="Enfriamiento_Simulado"
	  ;;

	4)
	  algo_name="Busqueda_Tabu"
	  ;;
	5)
	  algo_name="GRASP"
	  ;;
    6)
	  algo_name="Colonia_de_abejas"
	  ;;
	7)
	  algo_name="Algoritmo_Genetico"
	  ;;
esac
}

for i in $(ls); do
	if [ -d $i ]; then
		cd $i
		instance=$(pwd | sed "s/.*\/\(.*\)/\1/")
		echo "Getting best results of algorithms for instace $instance"
		file_name="${instance}-comp_algo.dat"
		for j in $(ls *.dat);do
			algo=$(echo $j | grep -o "Algoritmo-[0-7]" | grep -o "[0-9]")
			getAlgoName $algo
			echo " $algo : $algo_name" # >> ../${file_name}
			printf "$algo_name " >> ../${file_name}
			tail -n +2 $j | awk 'BEGIN { max=0 } $2 > max { max=$2; iter=$1 } END { print iter " " max }' FS=" " >> ../${file_name}
		done
		echo
		echo "$file_name max" >> ../test_prueba_I.txt
		cd ..
	fi
done
