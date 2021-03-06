#ifndef __TABUSEARCH_HPP__
#define __TABUSEARCH_HPP__

#include "neighborOperatorMSP.hpp"
#include "neighborExploratorMSP.hpp"
#include "TabuNeighExplorator.hpp"

//#include "DataFile.hpp"

#include <list>
#include <set>
#include <vector>
#include <ctime>
#include <cstdlib>

class TabuSearch {
	private:
		neighborOperatorMSP *_neighOp;
		TabuNeighExplorator *_explorator;
		int _globalOptimum;

	public:
		TabuSearch(TabuNeighExplorator &exp) {_explorator = &exp;}
		TabuSearch(TabuNeighExplorator &exp, neighborOperatorMSP &neighOp) {_neighOp = &neighOp; _explorator = &exp;}
		TabuSearch(neighborOperatorMSP &neighOp, TabuNeighExplorator &exp) {_neighOp = &neighOp; _explorator = &exp;}
		~TabuSearch() {}

		void setOperator(neighborOperatorMSP &nOperator) {_neighOp = &nOperator;}

		//Explores the current neighbourhood with the explorator with which the class was instantiated
		SolutionMSP apply(SolutionMSP &initialSol) {

			_globalOptimum = _neighOp->getClauses().size();

			SolutionMSP currSol = initialSol;
			SolutionMSP bestRet = currSol;

			currSol.setAptitude(_neighOp->getClauses());
			/* DEBUG INFO
				std::cout << "The initial solution has a fitness of " << currSol.getFitness()  << endl;
				cout << endl;
			*/

			clock_t time = clock();
			int i = 0;

			while(_TIME_MAX_ > ((clock() - time)/CLOCKS_PER_SEC)) {
				currSol = _explorator->exploreNg(currSol);

				currSol.setAptitude(_neighOp->getClauses());
				#ifdef DATA_AUTOMATIZATION
				std::cout << i << " " << currSol.getFitness() << " " << bestRet.getFitness() << endl;
				#else
				std::cout << i << ": ";
				std::cout << "Best Tabu Neighbour has fitness: " << currSol.getFitness() << " || Overall best has: " << bestRet.getFitness() << endl;
				#endif

				if(currSol.getFitness() > bestRet.getFitness()) {
					bestRet = currSol;
					bestRet.setAptitude(_neighOp->getClauses());
				}

				if(bestRet.getFitness() == _globalOptimum)
					break;

				i++;
			}

			return bestRet;
		}
};

#endif
