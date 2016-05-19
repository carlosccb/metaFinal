#ifndef		__NEIGHBOR_EXPLORATOR_MSP__
#define		__NEIGHBOR_EXPLORATOR_MSP__


#include <vector>

#include "Miscelanea.hpp"

#include "neighborOperatorMSP.hpp"

using namespace std;


class neighborExploratorMSP{


	private:

		neighborOperatorMSP _operador;


	public:

		//Constructores
		neighborExploratorMSP(){};
		neighborExploratorMSP(const neighborOperatorMSP &operador){

			_operador = operador;

		}

		neighborExploratorMSP & operator=(const neighborExploratorMSP &s){

			if(this != &s){

				this->_operador = s.getOperator();
			}

		  return *this;
		}


		//Modificadores
		void setOperator(neighborOperatorMSP &operador){_operador = operador;};

		//Observadores
		neighborOperatorMSP getOperator() const {return _operador;};

};






class firstImprovementMSP: public neighborExploratorMSP{



	public:

		//Constructores
		firstImprovementMSP(){};
		firstImprovementMSP(neighborOperatorMSP &operador): neighborExploratorMSP(operador){};



		//Metodo que explora el vecindario en funcion de la estrategia (best o first)
		SolutionMSP explorateNeighborhood(const SolutionMSP &initialSolution){


		  double actualFitness, bestFitness;
		  SolutionMSP bestSolution, actualSolution;


			bestSolution = initialSolution;
			bestFitness = bestSolution.getFitness();


			for(int i = 0; i < initialSolution.getSolution().size(); i++){


				actualSolution = getOperator().generateNeighbor(initialSolution, i);
				actualFitness = actualSolution.getFitness();


				if(actualFitness > bestFitness)

					return actualSolution;	//Devolvemos el nuevo optimo

			}


			return initialSolution;			//El optimo sigue siendo el mismo
		}
};







class bestImprovementMSP: public neighborExploratorMSP{



	public:

		//Constructores
		bestImprovementMSP(){};
		bestImprovementMSP(neighborOperatorMSP &operador): neighborExploratorMSP(operador){};



		//Metodo que explora el vecindario en funcion de la estrategia (best o first)
		SolutionMSP explorateNeighborhood(const SolutionMSP &initialSolution){

		  double actualFitness, bestFitness;
		  SolutionMSP bestSolution, actualSolution;

			bestSolution = initialSolution;
			bestFitness = bestSolution.getFitness();


			for(int i = 0; i < initialSolution.getSolution().size(); i++){


				actualSolution = getOperator().generateNeighbor(initialSolution, i);
				actualFitness = actualSolution.getFitness();


				if(actualFitness > bestFitness){

					bestFitness = actualFitness;
					bestSolution = actualSolution;
				}

			}


			return bestSolution;			//Devolvemos el ¿nuevo? optimo
		}


};




#endif
