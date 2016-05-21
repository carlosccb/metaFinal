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



using namespace std;



class GRASPExploratorMSP{



	private:

		localSearchMSP _busquedaLocal;


	public:


		GRASPExploratorMSP(){};
		GRASPExploratorMSP(const localSearchMSP &busquedaLocal){

			_busquedaLocal = busquedaLocal;
		}


		int mejorCandidato(const vector <problem_element> &info, vector <int> &candidatos){


			int posMejor = candidatos[0];
			double ratioMejor = info[candidatos[0]].a / info[candidatos[0]].b;		//beneficio / peso

			for(int i = 1; i < candidatos.size(); i++){


				double ratioActual = info[candidatos[i]].a / info[candidatos[i]].b;
				if( ratioActual > ratioMejor ){

					posMejor = candidatos[i];
					ratioMejor = ratioActual;
				}

			}

		  return posMejor;
		}



		SolutionMSP greedyConstructor(const vector <problem_element> &info){



			SolutionMSP solucionFinal(info.size());
			vector <int> aux;
			int numAux, i = 0;


			//Obtenemos el resto de elementos mediante un Greedy con una lista de elemntos aleatorios
			while(i < (info.size() / 10)){


				while(aux.size() < 10){	//Creamos una lista con 10 elementos aun no escogidos


					do{

						numAux = rand() % info.size();

					} while(solucionFinal.getSolution(numAux));
					aux.push_back(numAux);		//Introducimos en la lista de candidatos un elemento aleatorio que aun no este en la lista
				}


				int posMejor = mejorCandidato(info, aux);
				solucionFinal.setSolution(posMejor, true);

				aux.clear();

				i++;
			}


			solucionFinal.setAptitude(_busquedaLocal.getOperator().getMSPSize(), info);

		  return solucionFinal;
		}



		SolutionMSP GRASP(const vector <problem_element> &info){


			SolutionMSP actualSolution, currentSolution, bestSolution = greedyConstructor(info);
			double actualFitness, bestFitness = bestSolution.getFitness();


			for(int i = 0; i < 100; i++){

//				cout << "Iteracion: " << i << endl;
				currentSolution = greedyConstructor(info);
				_busquedaLocal.localOptimum(currentSolution, actualSolution, actualFitness);

				if(actualFitness > bestFitness){

					bestSolution = actualSolution;
					bestFitness = actualFitness;
				}
			}

		  return bestSolution;
		}




};


#endif
