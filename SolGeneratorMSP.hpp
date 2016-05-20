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

		SolutionMSP randomSolutionGenerator(unsigned int objetos) {

			SolutionMSP solucion(objetos);


			int incluidos = rand() % objetos;
			int pos;

			for (int i = 0; i < incluidos; i++){

				while(true){

					pos = rand() % objetos;
					if(solucion.getSolution(pos) == false)
						break;

				}

				solucion.setSolution(pos, true);
			}


			return solucion;
		}


};


#endif
