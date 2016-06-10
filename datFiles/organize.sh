for i in $(ls ../instances);do
	file_name=$(echo $i | sed "s/\(.*\)\.cnf/\1/")
	echo "The isolated file name is -> $file_name"
	mkdir $file_name
	for j in $(ls * | grep $file_name);do
		echo "  -> moving  $j with it's bros in $file_name"
		mv $j $file_name
	done
done
