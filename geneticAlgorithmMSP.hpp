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
		vector < vector <int> > _clauses;
		int _solutionSize;

	public:


		geneticAlgorithmMSP(const vector < vector <int> > &clauses, const int &solutionSize){

			_solutionSize = solutionSize;
			_clauses = clauses;
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

//				instancia.saveResults(contador, bestSolution, _population[_population.size() - 1]);

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
					newIndividual = solGenerator.randomSolutionGenerator(_MSPSize);
					newIndividual.setAptitude(_clauses);

					//Comprobamos que este lo suficientemente separado del resto de individuos
					for(int j = 0; j < auxiliarPopulation.size(); j++){

						//Comprobamos si la distancia de Hamming es mayor que L/4
						if( distanciaHamming(auxiliarPopulation[j], newIndividual) < (_solutionSize / 4) ){

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


		  int pA, pB;	//Posiciones de los padres dentro del vector de la poblacion
		  SolutionMSP child;

			selectParents(pA, pB);

			//Obtenemos una subpoblacion con los padres y los hijos que estos generan
			subPopulation = geneticOperator(pA, pB);

			//Dejamos en el vector solo a los dos mejores individuos
			selectIndividuals(newPopulation, child, pA, pB);
		}





		/*-----------------------------------------------------------------------

			Funcion que selecciona dos padres por el metodo Stochastic Universal
			Sampling, el cual funciona de forma similar al de la Ruleta, pero con
			tantos apuntadores como padres se quieran escoger

		------------------------------------------------------------------------*/

		void selectParents(int &pA, int &pB){



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

				if(valid)

					aux.push_back(numAux);

			}


			//Escogemos al mejor individuo de todos para ser uno de los padres

			pA = aux[0];
			for(int i = 1; i < aux.size(); i++){

				if(_population[aux[i]].getFitness() > _population[pA].getFitness())

					pA = aux[i];
			}


			aux.clear();


			//Hacemos el torneo para escoger al SEGUNDO padre
			while(potentialParents.size() < 5){

				numAux = rand() % _population.size();
				bool valid = true;

				for(int i = 0; i < aux.size(); i++){

					if(numAux == aux[i])
						valid = false;

				}

				if(valid)

					aux.push_back(numAux);


			}


			//Escogemos al segundo padre

			pB = aux[0];
			for(int i = 1; i < aux.size(); i++){

				if(_population[aux[i]].getFitness() > _population[pB].getFitness())

					pB = aux[i];
			}

		}




		/*-----------------------------------------------------------------------

			Funcion que lleva a cabo la reproduccion de dos individuos, escogiendo
			un punto de cruce, para despues ejecutar el algoritmo de entrecruzamiento

		------------------------------------------------------------------------*/


		SolutionMSP geneticOperator(const int &pA, const int &pB){

		  vector <bool> solucion;
		  SolutionMSP hijo;
		  int numAux;


			for(int i = 0; i < _population[pA].getSolution().size(); i++){

				if(_population[pA].getSolution(i) == _population[pB].getSolution(i))
					solucion.push_back(_population[pA].getSolution(i));

				else{

					numAux = rand() % 2;

					if(numAux == 0)
						solucion.push_back(_population[pA].getSolution(i));

					else
						solucion.push_back(_population[pB].getSolution(i));

				}
			}

			hijo.setSolution(solucion);
			hijo.setAptitude(_clauses);

		  return hijo;
		}




		//Funcion que escoge entre los dos mejores individuos despues de un cruce
		void selectIndividuals(vector <SolutionMSP> &newPopulation, const SolutionMSP &child, const int &pA, const int &pB){


			//El hijo es mejor que los dos padres
			if(child.getFitness() > _population[pA].getFitness() && child.getFitness() > _population[pB].getFitness()){

				//Añadimos al hijo a la nueva poblacion
				newPopulation.push_back(child);

				//Añadimos a uno de los dos padres
				if(_population[pA].getFitness() > _population[pB].getFitness()){

					newPopulation.push_back(_population[pA]);
					_population.erase(_population.begin() + pA);
				}

				else{

					newPopulation.push_back(_population[pB]);
					_population.erase(_population.begin() + pB);
				}
			}


			//El padre A es mejor que el hijo y el padre B
			else if(_population[pA].getFitness() > child.getFitness() && _population[pA].getFitness() > _population[pB].getFitness()){


				newPopulation.push_back(_population[pA]);
				_population.erase(_population.begin() + pA);


				if(child > _population[pB].getFitness()){

					newPopulation.push_back(child);
				}

				else{

					newPopulation.push_back(_population[pB]);
					_population.erase(_population.begin() + pB);
				}
			}



			//El mejor individuo de todos es el segundo padre
			else{


				newPopulation.push_back(_population[pB]);
				_population.erase(_population.begin() + pB);


				if(child > _population[pA].getFitness()){

					newPopulation.push_back(child);
				}

				else{

					newPopulation.push_back(_population[pA]);
					_population.erase(_population.begin() + pA);
				}
			}


		}	//FIN DE LA FUNCION



};


#endif
