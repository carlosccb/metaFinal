#ifndef __SOLUTIONMSP__
#define __SOLUTIONMSP__

#include <vector>

#include "Miscelanea.hpp"

using namespace std;

class solutionMSP{

	private:

		vector <bool> _solution;
		int _fitness;


	public:

		//Constructor
		solutionMSP(){};
		solutionMSP(int objetos=0){

			for (int i = 0; i < objetos; i++)
				_solution.push_back(false);
		}

		//Observadores
		inline vector<bool> getSolution() const {return _solution;};

		bool getSolution(const unsigned int &n) const{

			if (n <= _solution.size() - 1)
			  return _solution[n];
			else
			  return -1;
		};


		inline int getFitness() const {return _fitness;};


		//Modificadores
		inline void setSolution(const vector<bool> &solution) {_solution = solution;};
		inline void setFitness(const int &fitness){_fitness = fitness;};

		void setSolution(const unsigned int &pos, const bool &valor){

			if (pos <= _solution.size() - 1)
				_solution[pos]=valor;
		};


		//Sobrecarga Operador =
		solutionMSP & operator=(const solutionMSP &s){

			if(this != &s){

				this->_solution = s.getSolution();
				this->_fitness = s.getFitness();
			}

		  return *this;

		}


		//Funcion que devuelve la bondad de una solucion
		void setAptitude(const vector < vector <int> > &clauses){

		  int contador = 0, numVar;
		  bool clauseVar, valid;

			for(int i = 0; i < clauses.size(); i++){

				for(int j = 0; j < clauses[i].size(); j++){

					valid = true;
					numVar = abs(clauses[i][j]) - 1;

					//Comprobamos si la variable de la clausula es positiva o negativa
					if(clauses[i][j] < 0)
						clauseVar = false;

					else
						clauseVar = true;

					//Comprobamos si alguna de las clausulas termina siendo negativa
					if(_solution[numVar] && ! clauseVar){

						valid = false;
						break;
					}

					else if(! _solution[numVar] && ! clauseVar){

						valid = false;
						break;
					}

				}


				if(valid)
					contador++;		//La clausula se cumple

			}


			_fitness = contador;
		}



 };
#endif
