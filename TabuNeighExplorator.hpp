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
		std::list<int> _shortTermMemory;

	public:
		TabuNeighExplorator(neighborOperatorMSP *neighOperator) {_neighOperator = neighOperator;}
		~TabuNeighExplorator() {}

	std::list<int> difference(std::list<int> &v1, std::list<int> &v2) {
		std::list<int> v3;

		//List has it's own sort function, it doesn't work with the std's one
		v1.sort();
		v2.sort();

		std::set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(v3));

		return v3;
	}

	std::list<int> notExplored(int size) {
		std::list<int> range(size);
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

		//Genero el conjunto de vecinos aun no usados
		auto soltsNotExplored = notExplored(sol.getSolution().size());

		//Saco el ultimo elemento del conjunto de no usados y lo elimino
		int changed = soltsNotExplored.back();
		soltsNotExplored.pop_back();
		bestCurrent = _neighOperator->generateNeighbor(bestCurrent, changed);

		//Recorro el resto de soluciones no exploradas
		for(auto i: soltsNotExplored) {
			SolutionMSP aux = sol;

			//Guardo el resultado de cambiar una solucion no explorada
			aux = this->_neighOperator->generateNeighbor(aux, i);

			//Si es mejor que la anterior, guardo la actual
			if(aux.getFitness() >  bestCurrent.getFitness()) {
				if(not insertMemory(changed)) {
					cout << "Mi logica no funciona bien" << endl;
					exit(1);
				}

				changed = i;
				cout << "Mejor solucion en la posicion " << i << endl;
				bestCurrent = aux;
			}
		}

		if(not insertMemory(changed)) {
			cout << "elemento ya insertado en memoria" << endl;
			exit(1);
		}

		cout << "Changed element " << changed << endl;

		//std::cout << " || " << changed << " || shrtmem size: " << _shortTermMemory.size() << " || ";// << std::endl;
		//printVect(sol.getSolution(), ",", false);
		//std::cout << " || " << std::endl;

		return bestCurrent;
	}

//_________________________________________________________________________________________________________

};

#endif
