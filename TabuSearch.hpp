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

		void setOperator(neighborOperatorMSP &nOperator) {_neighOp = &nOperator;}

		//Explores the current neighbourhood with the explorator with which the class was instantiated
		SolutionMSP apply(SolutionMSP &initialSol) {
			SolutionMSP currSol = initialSol;
			SolutionMSP nextIter = initialSol;
			SolutionMSP bestRet = currSol;

			std::list<std::vector<bool>> mdTermMemory;

			currSol.setAptitude(_neighOp->getClauses());
			/* DEBUG INFO
				std::cout << "The initial solution has a fitness of " << currSol.getFitness()  << endl;
				cout << endl;
			*/

			for(unsigned int i = 0; i < 100'000; i++) {
				std::cout << i << ": " << std::endl;

				currSol = _explorator->exploreNg(currSol);

				currSol.setAptitude(_neighOp->getClauses());
				bestRet.setAptitude(_neighOp->getClauses());
				std::cout << " Best Tabu Neighbour has fitness: " << currSol.getFitness() << " || Overall best has: " << bestRet.getFitness();

				if(currSol.getFitness() > bestRet.getFitness()) {
					bestRet = currSol;
					//std::cout << " ||| => Found a better one: " << bestRet.getFitness();
				}

				cout << endl;

				std::cout << std::endl;
			}

			return bestRet;
		}

};

#endif
