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
//#include "geneticAlgorithmMSP.hpp"

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
	cout << "bestFitness (Inicio): " << bestFitness << endl;

	for(int i = 0; i < 10000; i++){

		currentSolution = g.randomSolutionGenerator(numVar);
		currentSolution.setAptitude(clauses);
		currentFitness = currentSolution.getFitness();


		if(currentFitness > bestFitness){

			bestSolution = currentSolution;
			bestFitness = currentFitness;
		}

		cout << "bestFitness (Iteracion " << i << "): " << bestFitness << " | currentFitness --> " << currentFitness << endl;


	}


	//Guardamos / imprimimos los resultados obtenidos

	cout << "bestFitness (Final): " << bestFitness << endl;

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

	cout << endl << "numero Variables = " << numVar << ", numero Clausulas = " << numCla << endl;
	cout << "bestFitness (Inicio): " << bestFitness << endl;

	for(int i = 0; i < 1000; i++){

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

		cout << "bestFitness (Iteracion " << i << "): " << bestFitness << " | currentFitness --> " << currentFitness << endl;


	}

	cout << "bestFitness (Final): " << bestFitness << endl;

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


	cout << endl << "numero Variables = " << numVar << ", numero Clausulas = " << numCla << endl;
	cout << "bestFitness (Inicio): " << initialSolution.getFitness() << endl;


  coolingExploratorMSP SA(operador);

	finalSolution = SA.enfriamientoSimuladoMSP(numVar, initialSolution);

	cout << "bestFitness (Final): " << finalSolution.getFitness() << endl;



}

void GRASPexplorator(const vector <vector <int> > &clauses, const int &numVar, const int &numCla){


  neighborOperatorMSP operador(clauses);
  firstImprovementMSP explorador(operador);
  localSearchMSP LS(operador, explorador);

  SolutionMSP initialSolution, finalSolution;


	cout << endl << "numero Variables = " << numVar << ", numero Clausulas = " << numCla << endl;
//	cout << "bestFitness (Inicio): " << initialSolution.getFitness() << endl;


  GRASPExploratorMSP G(LS);

	finalSolution = G.GRASP(numVar);

	cout << "bestFitness (Final): " << finalSolution.getFitness() << endl;


}

void TabuSearchMain(const vector <vector <int> > &clauses, const int &numVar, const int &numCla){
	cout << "NO HASE NADA NO MAS WEY" << endl;

}

void algoritmoGenetico();

#endif
