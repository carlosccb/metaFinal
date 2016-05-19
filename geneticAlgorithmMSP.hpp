#ifndef		__GENETIC_ALGORITHM_MSP__
#define		__GENETIC_ALGORITHM_MSP__


#include <cstdlib>
#include <cmath>
#include <vector>
#include <ctime>

#include "Miscelanea.hpp"

#include "SolutionMSP.hpp"
#include "SolGeneratorMSP.hpp"
#include "neighborOperatorMSP.hpp"
#include "neighborExploratorMSP.hpp"
#include "localSearchMSP.hpp"

#include <iostream>

#define POP_SIZE2 50
#define MAX 128

using namespace std;



class geneticAlgorithmMSP{



	private:

		vector <SolutionMSP> _population;
		vector <problem_element> _info;
		int _MSPSize;

	public:


		geneticAlgorithmMSP(const vector <problem_element> &info, const int &MSPSize){

			_MSPSize = MSPSize;
			_info = info;
		};

		~geneticAlgorithmMSP(){};



		/*-----------------------------------------------------------------------

			Funcion que implementa el algoritmo genetico para el MSP

			El tamaño de la poblacion siempre debe ser par para no complicar en exceso

		------------------------------------------------------------------------*/

		SolutionMSP GA(){



		  SolutionMSP bestSolution;
		  InstanceMSP instancia;
		  int contador = 1;		//Variable con el numero de iteraciones


			_population = initializePopulation(POP_SIZE2);	//Inicializamos la poblacion
			evaluatePopulation(_population);
			
			clock_t time = clock();
			double tiempo = 0;
			double hora = 3600.0;

			//Tras ordenar, el primer elemento de la poblacion es el mejor
			bestSolution = _population[_population.size() - 1];

                       
			while(contador < 100000 && tiempo < (1 * hora)){


			  vector <SolutionMSP> auxiliarPopulation;

				instancia.saveResults(contador, bestSolution, _population[_population.size() - 1]);

				//Creamos la nueva poblacion por completo
				while(auxiliarPopulation.size() < _population.size())

					evolvePopulation(auxiliarPopulation);


				evaluatePopulation(auxiliarPopulation);
				_population = auxiliarPopulation;


				if(bestSolution.getFitness() < _population[_population.size() - 1].getFitness())
					bestSolution = _population[_population.size() - 1];

				cout << "Iteracion: " << contador << "  --> " << bestSolution.getFitness() << endl;


				contador++;
				tiempo = ((clock() - time) / (double) CLOCKS_PER_SEC);
			}


		  return bestSolution;
		}




		/*-----------------------------------------------------------------------

			Funcion que genera la poblacion inicial por medio de un método de
			Diversificacion Secuencial:

				Se añaden soluciones a la poblacion que esten separadas
				lo suficiente en el espacio de busqueda (medido por una distancia
				de Hamming)

		------------------------------------------------------------------------*/

		vector <SolutionMSP> initializePopulation(const int &popSize){


		  vector <SolutionMSP> auxiliarPopulation;
		  SolGeneratorMSP solGenerator;

		  SolutionMSP newIndividual;

			for(int i = 0; i < popSize; i++){

				bool valid = false;

				while(! valid){

					valid = true;
					newIndividual = solGenerator.randomSolutionGenerator(_info.size());
					newIndividual.setAptitude(_MSPSize, _info);

					//Comprobamos que este lo suficientemente separado del resto de individuos
					for(int j = 0; j < auxiliarPopulation.size(); j++){

						//Comprobamos si la distancia de Hamming es mayor que L/4
						if( distanciaHamming(auxiliarPopulation[j], newIndividual) < (_info.size() / 4) ){

							valid = false;
							break;
						}
					}

				}

				cout << "Añadido individuo: " << i << endl;
				auxiliarPopulation.push_back(newIndividual);

			}

		  return auxiliarPopulation;
		}


		//Funcion que devulve la distancia de hamming entre dos soluciones
		int distanciaHamming(const SolutionMSP &sol1, const SolutionMSP &sol2){

		  int distHamming = 0;

			if(sol1.getSolution().size() != sol2.getSolution().size()){

				cout << endl << "Error. El tamaño de los vectores solucion no es similar" << endl << endl;
				exit(0);
			}

			for(int i = 0; i < sol1.getSolution().size(); i++){

				if(sol1.getSolution(i) != sol2.getSolution(i))
					distHamming++;
			}

			return distHamming;
		}




		/*-----------------------------------------------------------------------

			Funcion que ordena los inidividuos de la poblacion en funcion de su
			fitness, en orden descendente (del mejor individuo al peor, es decir,
			de la solucion con menor fitness a la de mayor valor de fitness)

		------------------------------------------------------------------------*/

		void evaluatePopulation(vector <SolutionMSP> &population){


		  unsigned int left = 0, pos = 0, seed = rand();
		  unsigned int stack[MAX];

		  unsigned int len = population.size();


			while (1) {

				for (; left+1 < len; len++){

		            if (pos == MAX)
		            	len = stack[pos = 0];


	            	  double pivot = population[left+seed%(len-left)].getFitness();

		            seed = seed*69069+1;
		            stack[pos++] = len;

					for (unsigned right = left-1; ; ) {

			            while (population[++right].getFitness() < pivot);
			            while (pivot < population[--len].getFitness());

			            if (right >= len)
			            	break;

		              SolutionMSP temp = population[right];

			            population[right] = population[len];
			            population[len] = temp;
					}
				}

	        	if (pos == 0)
			        break;

	        	left = len;
	        	len = stack[--pos];
			}

		}






		/*-----------------------------------------------------------------------

			Funcion que escoge a los dos mejores individuos del cruce de dos
			padres de la poblacion dada, y los añade a la nueva poblacion

		------------------------------------------------------------------------*/

		void evolvePopulation(vector <SolutionMSP> &newPopulation){


		  SolutionMSP pA, pB;
		  vector <SolutionMSP> subPopulation;

			selectParents(pA, pB);

			//Obtenemos una subpoblacion con los padres y los hijos que estos generan
			subPopulation = geneticOperator(pA, pB);

			//Dejamos en el vector solo a los dos mejores individuos
			selectIndividuals(subPopulation);


			newPopulation.push_back(subPopulation[0]);
			newPopulation.push_back(subPopulation[1]);
		}





		/*-----------------------------------------------------------------------

			Funcion que selecciona dos padres por el metodo Stochastic Universal
			Sampling, el cual funciona de forma similar al de la Ruleta, pero con
			tantos apuntadores como padres se quieran escoger

		------------------------------------------------------------------------*/

		void selectParents(SolutionMSP &pA, SolutionMSP &pB){



		  vector <SolutionMSP> potentialParents;
		  vector <int> aux;
		  int numAux;


			//Obtenemos padres potenciales de forma aleatoria de la poblacion
			while(potentialParents.size() < 5){

				numAux = rand() % _population.size();
				bool valid = true;

				for(int i = 0; i < aux.size(); i++){

					if(numAux == aux[i])
						valid = false;

				}

				if(valid){

					potentialParents.push_back(_population[numAux]);
					aux.push_back(numAux);
				}

			}

			//Escogemos al mejor individuo de todos para ser uno de los padres
			evaluatePopulation(potentialParents);
			pA = potentialParents[potentialParents.size() - 1];


			potentialParents.clear();
			aux.clear();


			//Hacemos el torneo para escoger al SEGUNDO padre
			while(potentialParents.size() < 5){

				numAux = rand() % _population.size();
				bool valid = true;

				for(int i = 0; i < aux.size(); i++){

					if(numAux == aux[i])
						valid = false;

				}

				if(valid){

					potentialParents.push_back(_population[numAux]);
					aux.push_back(numAux);
				}

			}

			evaluatePopulation(potentialParents);
			pB = potentialParents[potentialParents.size() - 1];

		}




		/*-----------------------------------------------------------------------

			Funcion que lleva a cabo la reproduccion de dos individuos, escogiendo
			un punto de cruce, para despues ejecutar el algoritmo de entrecruzamiento

		------------------------------------------------------------------------*/


		vector <SolutionMSP> geneticOperator(const SolutionMSP &pA, const SolutionMSP &pB){

		  vector <SolutionMSP> naturalOrder;
		  vector <bool> solucion;
		  SolutionMSP hijo;
		  int numAux;

			naturalOrder.push_back(pA);
			naturalOrder.push_back(pB);

			for(int i = 0; i < pA.getSolution().size(); i++){

				if(pA.getSolution(i) == pB.getSolution(i))
					solucion.push_back(pA.getSolution(i));

				else{

					numAux = rand() % 2;

					if(numAux == 0)
						solucion.push_back(pA.getSolution(i));

					else
						solucion.push_back(pB.getSolution(i));

				}
			}

			hijo.setSolution(solucion);
			hijo.setAptitude(_MSPSize, _info);
			naturalOrder.push_back(hijo);

		  return naturalOrder;
		}




		//Funcion que escoge entre los dos mejores individuos despues de un cruce
		void selectIndividuals(vector <SolutionMSP> &naturalOrder){


			evaluatePopulation(naturalOrder);

			while(naturalOrder.size() > 2)
				naturalOrder.erase( naturalOrder.begin());

		}



};


#endif
