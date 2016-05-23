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
			cout << "obj: " << objetos << std::endl;
			int incluidos = rand() % objetos;
			int pos;

			for(int i = 0; i < incluidos; i++) {

				while(true) {
					pos = rand() % objetos;
					if(solucion.getSolution(pos) == false)
						break;
				}
				std::cout << "len: " << objetos << " | pos: " << pos << std::endl;
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


		/* ----------------------------------------------------

			Funcion que genera una porcion de una solucion
		aleatoria, desde un punto a otro, manteniendo el resto
		de la solucion generada a false

		----------------------------------------------------- */

		SolutionMSP randomSolutionGenerator(const int &objetos, int p1, int p2) {

			SolutionMSP solucion(objetos);

			int dif = p2 - p1;

			//Creamos la solucion aleatoria parcial
			int incluidos = rand() % dif;
			int pos;

			for (int i = 0; i < incluidos; i++){

				while(true){

					pos = rand() % (p1 + dif);
					if(solucion.getSolution(pos) == false)
						break;

				}

				solucion.setSolution(pos, true);
			}


			return solucion;
		}






};


#endif
