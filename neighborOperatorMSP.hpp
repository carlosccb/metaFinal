#ifndef		__NEIGHBOR_OPERATOR_MSP__
#define		__NEIGHBOR_OPERATOR_MSP__

#include <vector>
#include <cmath>

#include "Miscelanea.hpp"

#include "SolucionMochila.hpp"


using namespace std;


class neighborOperatorMSP{


	private:

		int _MSPSize;						//Tamaño de la mochila
		vector <problem_element> _info;		//Informacion de cada elemento de la mochila

	public:

		//Constructor
		neighborOperatorMSP(){};
		neighborOperatorMSP(const int &KPSize, const vector <problem_element> &info){

			_MSPSize = KPSize;
			_info = info;
		};

		//Observadores
		vector <problem_element> getInfo() const {return _info;};
		int getMSPSize() const {return _KPSize;};

		//Sobrecarga operador =
		neighborOperatorMSP & operator=(const neighborOperatorKP &s){

			if(this != &s){

				this->_info = s.getInfo();
				this->_MSPSize = s.getKPSize();
			}

		  return *this;
		};

/*
		//Metodo que genera un vecino de una solucion, teniendo en cuenta unos parametros
		SolucionMochila generateNeighbor(SolucionMochila &initialSolution, vector<int> &parametros){

		int i;
		SolucionMochila solucion(initialSolution);

		for (i = 0; i < parametros.size(); i++){
			solucion.setSolucion(parametros[i], abs(solucion.getSolucion(parametros[i]) - 1));
		}


                return solucion;
		}
*/

		//Metodo que genera un vecino, invirtiendo un unico bit de una solucion dada
		SolucionMochila generateNeighbor(const SolucionMochila &initialSolution, int pos){

			SolucionMochila solucion(initialSolution);
			solucion.setSolucion(pos, abs(solucion.getSolucion(pos) - 1));
			solucion.recalcularFitness(pos, _info, _MSPSize);

		  return solucion;
		}


};

#endif
