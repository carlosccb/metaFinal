#ifndef __TABUNEIGHEXPLORATOR_HPP__
#define __TABUNEIGHEXPLORATOR_HPP__

#include <algorithm>
#include <numeric>
#include <set>
#include <list>
#include <vector>

#include "NeighOperator.hpp"
#include "NeighExplorator.hpp"

#include "Miscelanea.hpp"

template<class ProblemSolution, class Codification>
class TabuNeighExplorator : public NeighExplorator<ProblemSolution, Codification> {
	private:
		int _memorySize;
		std::list<Codification> _shortTermMemory;

	public:
		TabuNeighExplorator(NeighOperator<ProblemSolution> *neighOperator, bool maximize=true) : NeighExplorator<ProblemSolution, Codification>(neighOperator, maximize)  {}
		~TabuNeighExplorator() {}

	std::list<Codification> difference(std::list<Codification> &v1, std::list<Codification> &v2) {
		std::list<Codification> v3;

		//List has it's own sort function, it doesn't work with the std's one
		v1.sort();
		v2.sort();

		std::set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(v3));

		return v3;
	}

	std::list<Codification> notExplored(int size) {
		std::list<Codification> range(size);
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
	ProblemSolution exploreNg(ProblemSolution &sol) {
		//If this is the first time this class is used the memory's length is set to a third of the solution
		if(_shortTermMemory.empty())
			_memorySize = sol.getSolution().size() / 3;

		ProblemSolution bestCurrent = sol;
		auto soltsNotExplored = notExplored(sol.getSolution().size());
		int last = soltsNotExplored.back();
		int changed = last;
		soltsNotExplored.pop_back();
		NeighExplorator<ProblemSolution, Codification>::_neighOperator->apply(bestCurrent, last);

		for(auto i: soltsNotExplored) {
			ProblemSolution aux = sol;

			/*NeighExplorator<ProblemSolution, Codification>::*/this->_neighOperator->apply(aux, i);

			if(this->compare_fn(aux.getFitness(), bestCurrent.getFitness())) {
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
