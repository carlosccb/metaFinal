#ifndef		__GRASP_EXPLORATOR_MSP__
#define		__GRASP_EXPLORATOR_MSP__


#include <cstdlib>
#include <cmath>
#include <vector>

#include "Miscelanea.hpp"

#include "SolutionMSP.hpp"
#include "SolGeneratorMSP.hpp"
#include "neighborOperatorMSP.hpp"
#include "neighborExploratorMSP.hpp"
#include "localSearchMSP.hpp"

#include <iostream>

#define GP 4	//Numero de subsoluciones a generar para generar una solucion

using namespace std;



class GRASPExploratorMSP{



	private:

		localSearchMSP _busquedaLocal;
		int _globalOptimum;


	public:


		GRASPExploratorMSP(){};
		GRASPExploratorMSP(const localSearchMSP &busquedaLocal){

			_busquedaLocal = busquedaLocal;
		}



		/*

			Funcion que obtiene el caracter de una variable observando como se
			comporta en las clausulas en las que aparece. 

			Para ello almacenara el numero de veces que es positiva la variable
			en las clausulas, y el numero de veces que esta es negativa

																				*/

		vector <vector <int>> variableProbabilities(const int &problemSize, const vector <vector <int>> &clauses){


		  vector <vector <int>> p(problemSize, vector<int>(2,0));
		  int varNum;

			for(int i = 0; i < clauses.size(); i++){
				for(int j = 0; j < clauses[i].size(); j++){

					varNum = abs(clauses[i][j]) - 1;

					if(clauses[i][j] > 0)

						p[varNum][0]++;		//Valores positivos

					else

						p[varNum][1]++;		//Valores Negativos

				}

			}


		  return p;
		}




		SolutionMSP greedyConstructor(const int &problemSize){



			SolutionMSP solucionFinal(problemSize);

			bool fBool;
			int pos1, pos2;
			vector <vector <int>> prob;		//Matriz de n * 2


			prob = variableProbabilities(problemSize, _busquedaLocal.getOperator().getClauses());
			_globalOptimum = _busquedaLocal.getOperator().getClauses().size();

			for(int i = 0; i < problemSize; i++){


				fBool = rand() % (prob[i][0] + prob[i][1]) < prob[i][0];

				solucionFinal.setSolution(i, fBool);

			}


			solucionFinal.setAptitude(_busquedaLocal.getOperator().getClauses());

		  return solucionFinal;
		}



		SolutionMSP GRASP(const int &problemSize){


			SolutionMSP actualSolution, currentSolution, bestSolution = greedyConstructor(problemSize);
			int actualFitness, bestFitness = bestSolution.getFitness();


			clock_t time = clock();
			int i = 0;

			while(_TIME_MAX_ > ((clock() - time)/CLOCKS_PER_SEC)) {
//				cout << "Iteracion: " << i << endl;
				currentSolution = greedyConstructor(problemSize);
				actualSolution = _busquedaLocal.localOptimum(currentSolution);
				actualFitness = actualSolution.getFitness();

				if(actualFitness > bestFitness){

					bestSolution = actualSolution;
					bestFitness = actualFitness;
				}

				#ifndef DATA_AUTOMATIZATION
				cout << "bestFitness (Iteracion " << i << "): " << bestFitness << " | currentFitness --> " << currentSolution.getFitness() << endl;
				#else
				cout << i  << " " << currentSolution.getFitness() << " " << bestFitness << endl;
				#endif

				if(bestFitness == _globalOptimum)
					break;

				++i;
			}

		  return bestSolution;
		}




};


#endif
