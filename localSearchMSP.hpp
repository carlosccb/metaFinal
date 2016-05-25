#ifndef		__LOCAL_SEARCH_MSP__
#define		__LOCAL_SEARCH_MSP__


#include <vector>

#include "Miscelanea.hpp"

#include "neighborOperatorMSP.hpp"
#include "neighborExploratorMSP.hpp"
#include "SolutionMSP.hpp"


using namespace std;


class localSearchMSP{


	private:


		neighborOperatorMSP _operador;

		bestImprovementMSP _bestExplo;
		firstImprovementMSP _firstExplo;
		bool isBestExplorator;


	public:

		//Constructores
		localSearchMSP(){};
		localSearchMSP(neighborOperatorMSP &operador, firstImprovementMSP &explorador){

			_operador = operador;
			_firstExplo = explorador;

			isBestExplorator = false;
		}


		localSearchMSP(neighborOperatorMSP &operador, bestImprovementMSP &explorador){

			_operador = operador;
			_bestExplo = explorador;

			isBestExplorator = true;
		}


		//Sobrecarga operador igual
		localSearchMSP & operator=(const localSearchMSP &s){

			if(this != &s){

				this->_operador = s.getOperator();
				this->_bestExplo = s.getExploratorBest();
				this->_firstExplo = s.getExploratorFirst();

				this->isBestExplorator = s.exploratorType();
			}

		  return *this;
		};




		//Observadores
		neighborOperatorMSP getOperator() const {return _operador;};
		vector <vector<int>> getClauses() const {return _operador.getClauses();};

		bestImprovementMSP getExploratorBest() const {return _bestExplo;}
		firstImprovementMSP getExploratorFirst() const {return _firstExplo;}
		bool exploratorType() const {return isBestExplorator;}


		//Metodo que devuelve el optimo local ¿Y su valor de fitness?
		SolutionMSP localOptimum(const SolutionMSP &initialSolution){


		  int iteraciones = 1000, contador = 0;		//Cuenta el numero de veces que el optimo no varia
		  double actualFitness, bestFitness;
		  SolutionMSP actualSolution, bestSolution;


			bestSolution = initialSolution;
			bestFitness = bestSolution.getFitness();

			while(contador < 2){


				if(! isBestExplorator)

					actualSolution = _firstExplo.explorateNeighborhood(bestSolution);


				else

					actualSolution = _bestExplo.explorateNeighborhood(bestSolution);



				actualFitness = actualSolution.getFitness();


				/*

					La Solucion devuelta en cada iteracion solo puede ser igual o mejor que
				la antetior, porque se incluye a si misma en el vecindario para compararse

																							*/

				if(bestFitness == actualFitness)

					contador++;


				else{

					bestFitness = actualFitness;
					bestSolution = actualSolution;

					contador = 0;
				}


			}


		  return bestSolution;
		}


};

#endif
