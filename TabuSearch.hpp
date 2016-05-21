#ifndef __TABUSEARCH_HPP__
#define __TABUSEARCH_HPP__

#include "NeighOperator.hpp"
#include "NeighExplorator.hpp"

#include "DataFile.hpp"

#include "Metaheuristic.hpp"

#include <list>
#include <set>
#include <vector>

template<class ProblemSolution, class Codification>
class TabuSearch : public Metaheuristic<ProblemSolution, Codification> {
	private:
		//Memories
		//std::list<ProblemSolution> mdTermMemory;
		//std::list<ProblemSolution> lngTermMemory;

	public:
		TabuSearch(NeighExplorator<ProblemSolution, Codification> &exp) : Metaheuristic<ProblemSolution, Codification>(exp) {}
		TabuSearch(NeighExplorator<ProblemSolution, Codification> &exp, NeighOperator<ProblemSolution> &neighOp) : Metaheuristic<ProblemSolution, Codification>(exp, neighOp) {}
		~TabuSearch() {}

		void setOperator(NeighOperator<ProblemSolution> &nOperator) {this->neighOperator = &nOperator;}

		//Explores the current neighbourhood with the explorator with which the class was instantiated
		ProblemSolution apply(ProblemSolution &initialSol) {
			ProblemSolution currSol = initialSol;
			ProblemSolution bestRet = currSol;
			//ProblemSolution  = auxSol;
			std::list<std::vector<Codification>> mdTermMemory;
			//string fileName = "data-tabuSearch.txt"
			//DataFile tabuSearch(fileName);
			//The stop condition in this case is the generation of 100.000 solutions
			/*
				Si en la memoria a corto plazo guardo las soluciones actuales vecinas generadas me haría falta
				 guardarlas si en el explorador pruebo todo el vecindario
				Las soluciones se prueban de manera iterativa o aleatoria, tendría mas sentido iter si voy a explorar todo el vecindario
			*/
			for(unsigned int i = 0; i < 100000; i++) {
				//std::cout << "i: " << i << std::endl;
				//std::cout << " Trying with fitness: " << auxSol.getFitness() << std::endl;
				std::cout << i << ": " << std::endl;
				currSol = this->explorator->exploreNg(currSol);

				std::cout << " Best Tabu Neighbor has fitness: " << currSol.getFitness() << " || Current best has: " << bestRet.getFitness();
				//<<std::endl;

				//printVect(currSol.getSolution());
				if(currSol.getFitness() > bestRet.getFitness()) {
					bestRet = currSol;
					std::cout << " ||| => Found a better one: " << bestRet.getFitness();
				}

				auto pos = std::find(mdTermMemory.begin(), mdTermMemory.end(), currSol.getSolution());
				if(pos == mdTermMemory.end())
					mdTermMemory.push_back(currSol.getSolution());
				else {
					std::cout << "\nThis solution has already been found\n";
					exit(1);
				}

				std::cout << std::endl;
			}

			return bestRet;
		}

//________________________________________________________________________________________

};

#endif
