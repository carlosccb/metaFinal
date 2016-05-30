#ifndef __TABUNEIGHEXPLORATOR_HPP__
#define __TABUNEIGHEXPLORATOR_HPP__

#include <algorithm>
#include <numeric>
#include <set>
#include <list>
#include <vector>

#include "neighborOperatorMSP.hpp"
#include "neighborExploratorMSP.hpp"

#include "Miscelanea.hpp"

class TabuNeighExplorator {
	private:
		neighborOperatorMSP *_neighOperator;
		int _memorySize;
		std::list<bool> _shortTermMemory;

	public:
		TabuNeighExplorator(neighborOperatorMSP*neighOperator) {}
		~TabuNeighExplorator() {}

	std::list<bool> difference(std::list<bool> &v1, std::list<bool> &v2) {
		std::list<bool> v3;

		//List has it's own sort function, it doesn't work with the std's one
		v1.sort();
		v2.sort();

		std::set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(v3));

		return v3;
	}

	std::list<bool> notExplored(int size) {
		std::list<bool> range(size);
		std::iota(range.begin(), range.end(), 0);

		return difference(range, _shortTermMemory);
	}

	bool insertMemory(int &val) {
		if(_shortTermMemory.size() == _memorySize)
			_shortTermMemory.pop_front();

		auto pos = std::find(_shortTermMemory.begin(), _shortTermMemory.end(), val);
		if(pos == _shortTermMemory.end())
			_shortTermMemory.push_back(val);
		else
			return false;

		return true;
	}

	/*
	     Because this func has to return a solution even if it's worse than the original, I've to get the
	   first fitness from a real solution, because I can't compare with the original one, so I modify the
	   bestCurrent to hold a non-used permutation
	*/
	SolutionMSP exploreNg(SolutionMSP &sol) {
		//If this is the first time this class is used the memory's length is set to a third of the solution
		if(_shortTermMemory.empty())
			_memorySize = sol.getSolution().size() / 3;

		SolutionMSP bestCurrent = sol;
		auto soltsNotExplored = notExplored(sol.getSolution().size());
		int last = soltsNotExplored.back();
		int changed = last;
		soltsNotExplored.pop_back();
		_neighOperator->generateNeighbor(bestCurrent, last);

		for(auto i: soltsNotExplored) {
			SolutionMSP aux = sol;

			this->_neighOperator->generateNeighbor(aux, i);

			if(aux.getFitness() >  bestCurrent.getFitness()) {
				changed = i;
				bestCurrent = aux;
			}
		}

		if(not insertMemory(changed))
			exit(1);

		//std::cout << " || " << changed << " || shrtmem size: " << _shortTermMemory.size() << " || ";// << std::endl;
		//printVect(sol.getSolution(), ",", false);
		//std::cout << " || " << std::endl;

		return bestCurrent;
	}

//_________________________________________________________________________________________________________

};

#endif
