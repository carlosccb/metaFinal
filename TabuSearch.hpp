#ifndef __TABUSEARCH_HPP__
#define __TABUSEARCH_HPP__

#include "neighborOperatorMSP.hpp"
#include "neighborExploratorMSP.hpp"
#include "TabuNeighExplorator.hpp"

//#include "DataFile.hpp"

//#include "Metaheuristic.hpp"

#include <list>
#include <set>
#include <vector>

class TabuSearch {
	private:
		neighborOperatorMSP *_neighOp;
		TabuNeighExplorator *_explorator;
		//Memories
		//std::list mdTermMemory;
		//std::list lngTermMemory;

	public:
		TabuSearch(TabuNeighExplorator &exp) {_explorator = &exp;}
		TabuSearch(TabuNeighExplorator &exp, neighborOperatorMSP &neighOp) {_neighOp = &neighOp; _explorator = &exp;}
		TabuSearch(neighborOperatorMSP &neighOp, TabuNeighExplorator &exp) {_neighOp = &neighOp; _explorator = &exp;}
		~TabuSearch() {}

		//void setOperator(neighborOperatorMSP &nOperator) {this->_neighOperator = &nOperator;}

		//Explores the current neighbourhood with the explorator with which the class was instantiated
		SolutionMSP apply(SolutionMSP &initialSol) {
			SolutionMSP currSol = initialSol;
			SolutionMSP nextIter = initialSol;
			SolutionMSP bestRet = currSol;

			std::list<std::vector<bool>> mdTermMemory;

			currSol.setAptitude(_neighOp->getClauses());
			std::cout << "The initial solution has a fitness of " << currSol.getFitness()  << endl;
				cout << endl;

			for(unsigned int i = 0; i < 100'000; i++) {
				//std::cout << " Trying with fitness: " << auxSol.getFitness() << std::endl;
				std::cout << i << ": " << std::endl;
				currSol = this->_explorator->exploreNg(currSol);

				currSol.setAptitude(_neighOp->getClauses());

				std::cout << " Best Tabu Neighbor has fitness: " << currSol.getFitness() << " || Current best has: " << bestRet.getFitness();

				if(currSol.getFitness() > bestRet.getFitness()) {
					bestRet = currSol;
					std::cout << " ||| => Found a better one: " << bestRet.getFitness();
				}
				cout << endl;

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
