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

		std::list<int> set_diff(const list<int> &v1, const list<int> &v2) {
			list<int> v3;
			bool insert = true;

			for(auto i: v1) {
				for(auto j: v2) {
					if(i == j) {
						insert = false;
						break;
					}
				}
				if(insert)
					v3.push_back(i);
				insert = true;
			}

			return v3;
		}

		std::list<int> notExplored(int size) {
			std::list<int> range(size);
			std::iota(range.begin(), range.end(), 0);

			return set_diff(range, _shortTermMemory);
		}

		bool insertMemory(int &val) {
			//Si el elemento ya esta en la memoria ha habido un error, se devuelve false
			if(std::find(_shortTermMemory.begin(), _shortTermMemory.end(), val) != _shortTermMemory.end())
				return false;

			if(_shortTermMemory.size() == _memorySize)
				_shortTermMemory.pop_front();

			_shortTermMemory.push_back(val);

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
			SolutionMSP aux;
			for(auto i: soltsNotExplored) {
				aux = sol;

				//Guardo el resultado de cambiar una solucion no explorada
				aux = this->_neighOperator->generateNeighbor(aux, i);

				//Si es mejor que la anterior, guardo la actual
				if(aux.getFitness() >  bestCurrent.getFitness()) {
					changed = i;
					bestCurrent = aux;
				}
			}

			if(not insertMemory(changed)) {
				cout << "elemento ya insertado en memoria" << endl;
				exit(1);
			}

			return bestCurrent;
		}

//_________________________________________________________________________________________________________

};

#endif
