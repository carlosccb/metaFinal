#ifndef _BCO_
#define _BCO_

#include "neighborOperatorMSP.hpp"
#include "SolGeneratorMSP.hpp"
#include "SolutionMSP.hpp"
#include "BeeWorker.hpp"
#include "BeeSupervisor.hpp"
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

class BCO{

private:

neighborOperatorMSP _operador;

vector<BeeWorker> _workers;

vector<BeeSupervisor> _supervisors;

int BeeMax = 5; //usad siempre minimo 3, o habría que cambiar la forma en la que mandas a las supervisoras

SolutionMSP _best;



public:


BCO(vector < vector <int> > &clauses){
	srand(time(NULL));

	neighborOperatorMSP operador(clauses);

	_operador = operador;

	for (int i = 0; i < BeeMax; i++){

		SolGeneratorMSP generator;
		BeeWorker worker(generator.randomSolutionGenerator(clauses[0].size()));
		_workers.push_back(worker);
		BeeSupervisor supervisor;
		_supervisors.push_back(supervisor);
		_best = generator.randomSolutionGenerator(clauses[0].size());
		_best.setAptitude(clauses);

		}


}


SolutionMSP beeColony() {

	clock_t time = clock();

	float time_max = 300.0;

	int iter = 0;

	while(time_max > ((clock() - time)/CLOCKS_PER_SEC)){
		
		for(int i = 0; i < BeeMax; i++){
			_workers[i].work(_operador);
			}
	sort(_workers.begin(), _workers.end(), comparar);

		for(int i = 0; i < BeeMax; i++){
			_supervisors[i].supervision(_operador, _workers);
			}

		for(int i = 0; i < BeeMax; i++){
			if (_workers[i].getSolution().getFitness() > _best.getFitness())
				_best = _workers[i].getSolution();
			if (_supervisors[i].getSolution().getFitness() > _best.getFitness())
				_best = _supervisors[i].getSolution();
			}

		//#ifndef DATA_AUTOMATIZATION
		//cout << "i: " << iter << " " << _best.getFitness()  << endl;
		//++iter;
		//#endif
	}

	return _best;
}



};
#endif
