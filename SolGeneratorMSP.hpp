#ifndef __SOL_GENERATOR_MSP_HPP__
#define __SOL_GENERATOR_MSP_HPP__

#include <vector>
#include <cstdlib>
#include <ctime>
#include <vector>

#include "Miscelanea.hpp"

using namespace std;


class SolGeneratorMSP{


	public:


		/* ----------------------------------------------------

			Funcion que genera una nueva solucion aleatoria
		decidiendo el numero de elementos que se incluiran en la
		mochila, y despues en que posiciones

		----------------------------------------------------- */

		SolutionMSP randomSolutionGenerator(const int &objetos) {

			SolutionMSP solucion(objetos);
			int incluidos = rand() % objetos;
			int pos;

			for(int i = 0; i < incluidos; i++) {

				while(true) {
					pos = rand() % objetos;
					if(solucion.getSolution(pos) == false)
						break;
				}

				solucion.setSolution(pos, true);
			}


			return solucion;
		}


		void randomSolutionGenerator(SolutionMSP &solution) {
			int objetos = solution.getSolution().size() - 1;
			int incluidos = rand()%objetos;

			for(unsigned int i = 0; i < incluidos; i++) {
				int pos = rand()%objetos;
				solution.setSolution(pos, true);
			}
		}



};


#endif
