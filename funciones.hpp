

/*------------------------------------------------------------------------------------


	Para que no se nos vaya de las manos el tamaño del main, aqui crearemos una
	funcion por cada uno de los metodos metaheuristicos.

	En cada una de las funciones implementaremos lo que deberia hacer el main
	para cada metodo, es decir, llevara a cabo el algoritmo con unos parametros
	y almacenara los datos de la salida en un fichero determinado.

	El main se encargara solo de obtener que tipo de algoritmo queremos ejecutar
	y con que parametros y llamar a la funcion que deba con un switch.


------------------------------------------------------------------------------------*/


void busquedaAleatoria(const vector <vector <int> > &clauses, const int &numVar, const int &numCla){


  SolutionMSP bestSolution, currentSolution;
  SolGeneratorMSP g;
  int bestFitness, currentFitness;


	//Llevamos a cabo el metodo
	bestSolution = g.randomSolutionGenerator(numVar);
	bestSolution.setAptitude(clauses);
	bestFitness = bestSolution.getFitness();

	cout << endl << "numero Variables = " << numVar << ", numero Clausulas = " << numCla << endl;

	cout << "bestFitness = " << bestFitness << endl;

	for(int i = 0; i < 100; i++){

		currentSolution = g.randomSolutionGenerator(numVar);
		currentSolution.setAptitude(clauses);
		currentFitness = currentSolution.getFitness();

/*
		cout << "currentFitness = " << currentFitness << "----> ";
		for(int i = 0; i < numVar; i++){


			cout << currentSolution.getSolution(i) << " ";

		}

		cout << endl;
*/

		if(currentFitness > bestFitness){

			bestSolution = currentSolution;
			bestFitness = currentFitness;
		}

	}


	//Guardamos / imprimimos los resultados obtenidos

	cout << "bestFitness = " << bestFitness << endl;

/*
	cout << "bestSolution: " << endl;
	for(int i = 0; i < numVar; i++){


		cout << bestSolution.getSolution(i) << " ";

	}

	cout << endl;
*/


}

void busquedaLocal();

void enfriamientoSimulado();

void GRASP();	//La funcion del GRASP se llama exactamente igual

void algoritmoGenetico();
