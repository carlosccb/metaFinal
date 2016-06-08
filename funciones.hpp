#ifndef __FUNCIONES_HPP__
#define __FUNCIONES_HPP__

#include "SolutionMSP.hpp"
#include "SolGeneratorMSP.hpp"
#include "neighborOperatorMSP.hpp"
#include "neighborExploratorMSP.hpp"
#include "localSearchMSP.hpp"
#include "coolingExploratorMSP.hpp"
#include "GRASPExploratorMSP.hpp"
#include "TabuSearch.hpp"
#include "TabuNeighExplorator.hpp"
#include "TabuSearch.hpp"
#include "geneticAlgorithmMSP.hpp"

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

	#ifndef DATA_AUTOMATIZATION
	cout << endl << "numero Variables = " << numVar << ", numero Clausulas = " << numCla << endl;
	cout << "bestFitness (Inicio): " << bestFitness << endl;
	#endif

	clock_t time = clock();
	int i = 0;

	while(_TIME_MAX_ > ((clock() - time)/CLOCKS_PER_SEC)) {
	//for(int i = 0; i < 10000; i++){

		currentSolution = g.randomSolutionGenerator(numVar);
		currentSolution.setAptitude(clauses);
		currentFitness = currentSolution.getFitness();


		if(currentFitness > bestFitness){

			bestSolution = currentSolution;
			bestFitness = currentFitness;
		}

		#ifndef DATA_AUTOMATIZATION
		cout << "bestFitness (Iteracion " << i << "): " << bestFitness << " | currentFitness --> " << currentFitness << endl;
		#else
		cout << i  << " " << currentFitness << " " << bestFitness << endl;
		#endif

		i++;
	}


	//Guardamos / imprimimos los resultados obtenidos

	#ifndef DATA_AUTOMATIZATION
	cout << "bestFitness (Final): " << bestFitness << endl;
	#endif

}


/*------------------------------------------------------------------------------------


	Funcion que ejecuta la busqueda local e imprime y guarda los resultados obtenidos

------------------------------------------------------------------------------------*/



void busquedaLocal(localSearchMSP &LS, const int &numVar, const int &numCla){


  SolutionMSP currentSolution, bestSolution;
  int currentFitness, bestFitness;
  SolGeneratorMSP g;


	bestSolution = g.randomSolutionGenerator(numVar);
	bestSolution.setAptitude(LS.getClauses());
	bestFitness = bestSolution.getFitness();

	#ifndef DATA_AUTOMATIZATION
	cout << endl << "numero Variables = " << numVar << ", numero Clausulas = " << numCla << endl;
	cout << "bestFitness (Inicio): " << bestFitness << endl;
	#endif

	clock_t time = clock();
	int i = 0;

	while(_TIME_MAX_ > ((clock() - time)/CLOCKS_PER_SEC)) {
		//Generamos la solucion aleatoria
		currentSolution = g.randomSolutionGenerator(numVar);
		currentSolution.setAptitude(LS.getClauses());

		//Aplicamos la busqueda local a dicha solucion
		currentSolution = LS.localOptimum(currentSolution);
		currentFitness = currentSolution.getFitness();


		if(currentFitness > bestFitness){

			bestSolution = currentSolution;
			bestFitness = currentFitness;
		}

		#ifndef DATA_AUTOMATIZATION
		cout << "bestFitness (Iteracion " << i << "): " << bestFitness << " | currentFitness --> " << currentFitness << endl;
		#else
		cout << i  << " " << currentFitness << " " << bestFitness << endl;
		#endif

		++i;
	}

	#ifndef DATA_AUTOMATIZATION
	cout << "bestFitness (Final): " << bestFitness << endl;
	#endif

}




/*------------------------------------------------------------------------------------


	Funcion que ejecuta el enfriamiento simulado e imprime y guarda los resultados 
	obtenidos en un fichero de texto

------------------------------------------------------------------------------------*/


void enfriamientoSimulado(const vector <vector <int> > &clauses, const int &numVar, const int &numCla){


  neighborOperatorMSP operador(clauses);
  SolGeneratorMSP g;

  SolutionMSP initialSolution, finalSolution;


	initialSolution = g.randomSolutionGenerator(numVar);
	initialSolution.setAptitude(clauses);


	#ifndef DATA_AUTOMATIZATION
	cout << endl << "numero Variables = " << numVar << ", numero Clausulas = " << numCla << endl;
	cout << "bestFitness (Inicio): " << initialSolution.getFitness() << endl;
	#endif


  coolingExploratorMSP SA(operador);

	finalSolution = SA.enfriamientoSimuladoMSP(numVar, initialSolution);

	#ifndef DATA_AUTOMATIZATION
	cout << "bestFitness (Final): " << finalSolution.getFitness() << endl;
	#endif



}

void GRASPexplorator(const vector <vector <int> > &clauses, const int &numVar, const int &numCla){


  neighborOperatorMSP operador(clauses);
  firstImprovementMSP explorador(operador);
  localSearchMSP LS(operador, explorador);

  SolutionMSP initialSolution, finalSolution;


	#ifndef DATA_AUTOMATIZATION
	cout << endl << "numero Variables = " << numVar << ", numero Clausulas = " << numCla << endl;
//	cout << "bestFitness (Inicio): " << initialSolution.getFitness() << endl;
	#endif


  GRASPExploratorMSP G(LS);

	finalSolution = G.GRASP(numVar);

	#ifndef DATA_AUTOMATIZATION
	cout << "bestFitness (Final): " << finalSolution.getFitness() << endl;
	#endif


}

void TabuSearchMain(const vector <vector <int> > &clauses, const int &numVar, const int &numCla){

	neighborOperatorMSP operador(clauses);
	firstImprovementMSP explorador(operador);
	TabuNeighExplorator ts_exp(&operador);
	TabuSearch TS(operador, ts_exp);
	SolGeneratorMSP randSolGen;

	SolutionMSP initialSolution, finalSolution;

	//initialSolution.setAptitude(clauses);

	#ifndef DATA_AUTOMATIZATION
	cout << endl << "numero Variables = " << numVar << ", numero Clausulas = " << numCla << endl;
	#endif
	//cout << "bestFitness (Inicio): " << initialSolution.getFitness() << endl;

	initialSolution = randSolGen.randomSolutionGenerator(numVar);
	initialSolution.setAptitude(clauses);

	finalSolution = TS.apply(initialSolution);

	#ifndef DATA_AUTOMATIZATION
	cout << "bestFitness (Final): " << finalSolution.getFitness() << endl;
	#endif

}

void algoritmoGenetico(const vector <vector <int> > &clauses, const int &numVar, const int &numCla){


  geneticAlgorithmMSP aReproducirse(clauses, numVar);
  SolutionMSP finalSolution;

	finalSolution = aReproducirse.GA();
	#ifndef DATA_AUTOMATIZATION
	cout << "bestFitness (Final): " << finalSolution.getFitness() << endl;
	#endif

}

void beeColonyOptimization(vector< vector<int> > &clauses){
	
	BCO metodo(clauses);
	SolutionMSP solucion;

	solucion = metodo.beeColony();
	#ifndef DATA_AUTOMATIZATION
	cout << endl << "bestFitness (Final): " << solucion.getFitness() << endl;
	#endif
	
	
}



#endif
