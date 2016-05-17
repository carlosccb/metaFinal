#ifndef __GENERATOR_MSP_HPP__
#define __GENERATOR_MSP_HPP__

#include <vector>
#include <cstdlib>
#include <ctime>
#include <vector>

#include "../lib/Miscelanea.hpp"

using namespace std;


class generatorMSP{


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
					if(solucion.getSolucion(pos) == false)
						break;

				}

				solucion.setSolucion(pos, true);
			}


			return solucion;
		}


};


#endif
