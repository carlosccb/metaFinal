#ifndef		__NEIGHBOR_OPERATOR_MSP__
#define		__NEIGHBOR_OPERATOR_MSP__

#include <vector>
#include <cmath>

#include "Miscelanea.hpp"

#include "SolutionMSP.hpp"


using namespace std;


class neighborOperatorMSP{


	private:

		vector < vector <int> > _clauses;		//Clausulas de la instancia

	public:

		//Constructor
		neighborOperatorMSP(){};
		neighborOperatorMSP(const vector < vector <int> > &clauses){_clauses = clauses;};

		//Observadores
		vector < vector <int> > getClauses() const {return _clauses;};

		//Sobrecarga operador =
		neighborOperatorMSP & operator=(const neighborOperatorMSP &s){

			if(this != &s)

				this->_clauses = s.getClauses();


		  return *this;
		};

/*
		//Metodo que genera un vecino de una solucion, teniendo en cuenta unos parametros
		SolutionMSP generateNeighbor(SolutionMSP &initialSolution, vector<int> &parametros){

		int i;
		SolutionMSP solucion(initialSolution);

		for (i = 0; i < parametros.size(); i++){
			solucion.setSolution(parametros[i], abs(solucion.getSolution(parametros[i]) - 1));
		}


                return solucion;
		}
*/

		//Metodo que genera un vecino, invirtiendo un unico bit de una solucion dada
		SolutionMSP generateNeighbor(const SolutionMSP &initialSolution, int pos){

			SolutionMSP solucion(initialSolution);
			solucion.setSolution(pos, abs(solucion.getSolution(pos) - 1));
			solucion.setAptitude(_clauses);

		  return solucion;
		}


};

#endif
