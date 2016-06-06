#ifndef _BEE_WORKER_
#define _BEE_WORKER_

#include "neighborOperatorMSP.hpp"
#include "SolutionMSP.hpp"
#include "SolGeneratorMSP.hpp"



class BeeWorker{


private:

SolutionMSP _solution;

vector < vector <int> > _clauses;

int _works;

int worksMAX = 100;

public:


BeeWorker(SolutionMSP solution, vector < vector <int> > &clauses){
	_solution = solution;
	_works = 0;
	_clauses = clauses;
}


void work(neighborOperatorMSP operador){

	if(_works < worksMAX){
		SolutionMSP aux;
		aux = operador.generateNeighbor(_solution, rand()%_solution.getSolution().size());
		
		if(aux.getFitness() > _solution.getFitness()){
			_works = 0;
			_solution = aux;
			}else _works = _works + 1;

	}	else{
		SolGeneratorMSP generador;
		_solution = generador.randomSolutionGenerator(_solution.getSolution().size());
		_solution.setAptitude(_clauses);
		_works = 0;
		}

}

SolutionMSP getSolution(){return _solution;}
};


bool comparar(BeeWorker &b, BeeWorker &B){

	if (b.getSolution().getFitness() > B.getSolution().getFitness()) return true;
		else return false;


}




#endif
