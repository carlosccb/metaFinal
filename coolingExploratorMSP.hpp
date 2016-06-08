#ifndef		__COOLING_EXPLORATOR_MSP__
#define		__COOLING_EXPLORATOR_MSP__


#include <cstdlib>
#include <cmath>
#include <vector>

#include "Miscelanea.hpp"

#include "SolutionMSP.hpp"
#include "neighborOperatorMSP.hpp"
#include <iostream>

#define TAM_TORNEO 5.0


using namespace std;



class coolingExploratorMSP{


	private:

		neighborOperatorMSP _operador;
		double _temperature;		//Hay que darle una temperatura inicial
		int _globalOptimum;


	public:

		//Constructores
		coolingExploratorMSP(){};
		coolingExploratorMSP(neighborOperatorMSP &operador){

			_operador = operador;

		}


		//Sobrecarga operador igual
		coolingExploratorMSP & operator=(const coolingExploratorMSP &s){

			if(this != &s){

				this->_operador = s.getOperator();
			}

		  return *this;
		};

		//Modificadores
		void setOperator(neighborOperatorMSP &operador){_operador = operador;};

		//Observadores
		neighborOperatorMSP getOperator() const {return _operador;};


		//Funciones pequeñas

		void temperatureRestart(const int &problemSize){

		  double media = 0.0;
		  SolGeneratorMSP g;

			for(unsigned int i = 0; i < TAM_TORNEO; i++){


				int pos1 = random() % problemSize;

				SolutionMSP original = g.randomSolutionGenerator(problemSize);
				original.setAptitude(_operador.getClauses());
				int fitness1 = original.getFitness();

				SolutionMSP vecino = getOperator().generateNeighbor(original, pos1);
				int fitness2 = vecino.getFitness();

				media += fabs(fitness2 - fitness1);

			}

			media /= TAM_TORNEO;
			//Dependiendo de si se quiere maximizar o minimizar, sera o no negativa la diferencia
			_temperature = (double) (-media) / log(0.9);

		}

		void coolingDown(){


			//La constante de enfriamiento geometrica debe estar entre 0.5 y 0.99
			_temperature = 0.990025 * _temperature;
		}


		bool accept(const int &actualFitness, const int &newFitness){


			//Tener en mente el tipo de optimizacion a la hora de implementar esta funcion

			if(newFitness > actualFitness)
				return true;

			int incE = actualFitness - newFitness;
			int k = 1;	//De donde carajo sale esta constante ????????

			float val = (float)rand()/RAND_MAX;
			if(exp(-incE/(k * _temperature)) > val)		//0.5 puede ser cambiado (Es el limite para probabilidades binarias)
				return true;


		  return false;
		}






		//Funciones tochas

		SolutionMSP enfriamientoSimuladoMSP(const int &problemSize, SolutionMSP &initialSolution){

			_globalOptimum = _operador.getClauses().size();


			temperatureRestart(problemSize);

		  int actualFitness, newFitness, bestFitness;
		  SolutionMSP bestSolution, actualSolution, newSolution;


			actualSolution = bestSolution = initialSolution;
			actualFitness = bestFitness = bestSolution.getFitness();


			clock_t time = clock();
			int k = 0;

			while(_TIME_MAX_ > ((clock() - time)/CLOCKS_PER_SEC)) {

				//cout << "Iteracion: " << k << endl;

				int pos1 = random() % problemSize;
				newSolution = getOperator().generateNeighbor(actualSolution, pos1);
				newFitness = newSolution.getFitness();


				//Si la solucion generada es mejor, la guardamos
				if(newFitness > bestFitness){

					bestSolution = newSolution;
					bestFitness = newFitness;
				}


				//Vemos si aceptamos o no la nueva solucion para generar vecinos a partir de ella
				if(accept(actualFitness, newFitness)){

					actualSolution = newSolution;
					actualFitness = newFitness;
				}

				#ifndef DATA_AUTOMATIZATION
				cout << "bestFitness (Iteracion " << k << "): " << bestFitness << " | currentFitness --> " << actualFitness << endl;
				#else
				cout << k << " " << actualFitness << " " << bestFitness << endl;
				#endif

				if(bestFitness == _globalOptimum)
					break;

				coolingDown();	//Descendemos la temperatura
				k++;
			}


			return bestSolution;

		}







};


#endif
