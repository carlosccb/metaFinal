#ifndef _BEE_SUPERVISOR_
#define _BEE_SUPERVISOR_

#include "neighborOperatorMSP.hpp"
#include "SolutionMSP.hpp"
#include "SolGeneratorMSP.hpp"
#include "BeeWorker.hpp"
#include <vector>





class BeeSupervisor{

private:

SolutionMSP _solution;


public:

void supervision(neighborOperatorMSP operador, vector<BeeWorker> workers){
	int aleatorio = rand()%3;
	_solution = operador.generateNeighbor(workers[aleatorio].getSolution(), rand()%(workers[aleatorio].getSolution().getSolution().size()));
}

SolutionMSP getSolution() {return _solution;};


};
#endif
