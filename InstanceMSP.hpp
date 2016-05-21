#ifndef __INSTANCE_MSP_HPP__
#define __INSTANCE_MSP_HPP__

#include <fstream>
#include <iostream>
#include <limits>
#include <regex>
#include <string>
#include <vector>

#include "Instance.hpp"
#include "Miscelanea.hpp"
#include "SolutionMSP.hpp"

using namespace std;

class InstanceMSP : public Instance {

	private:

		int _capacity_line;

	public:

		InstanceMSP() {}

		//Valores del constructor adaptados a los archivos csv de esta practica
		InstanceMSP(string file_name): Instance(file_name){};

		~InstanceMSP(){

			if(_file.is_open())
				_file.close();
		}


		//Funcion que almacena en un fichero una serie de datos de salida del programa
		void saveResults(const SolutionMSP &inicial, const double &best_fitness, const SolutionMSP &best_solution, double &tiempo, int iteraciones = 0){


		  int id = 1;	//Identificador del numero de ejecucion del programa
		  string line;

		  ifstream fr("MSP_Fitness&Time.txt");

			//Contamos cual ejecucion del programa es esta
			if(fr.is_open()){
				while(! fr.eof()){

					getline(fr, line);
					id++;
				}
			}

			fr.close();


		  ofstream fs("MSP_soluciones.txt", std::ofstream::app);	//Abrimos el flujo de salida al fichero


			//Escribimos los resultados de esta ejecucion
			fs << "Ejecución " << id << ":"<< endl;
                        for (int i = 0; i < best_solution.getSolution().size(); i++){
                             fs << i << " ";
                               if (best_solution.getSolution(i) == true){ fs << "Si " << 1 << " ";}
                                else { fs << "No " << 0 << " ";}
                               if (inicial.getSolution(i) == true){ fs << "Si " << 1 << endl;}
                                else {fs << "No " << 0 << endl;}

                        }
                        fs << "Fitness inicial: " << inicial.getFitness() << " Fitness mejora:" << best_fitness << "\t" << " Tiempo de ejecución: " << tiempo << endl;
                        fs << endl << endl << endl << endl;

			fs.close();

                  fs.open("MSP_Fitness&Time.txt", std::ofstream::app);
                  if (id != 1) fs << endl;
                   fs << id << " " << inicial.getFitness() << " " << best_fitness << " " <<  tiempo <<  " " << iteraciones;
                  fs.close();

		}



		void saveResults(const int &it, const SolutionMSP &best_global, const SolutionMSP &best_actual){


		  string line;
		  ofstream fs;

			fs.open("MSP_Iteraciones.txt", std::ofstream::app);

			fs << it << " " << best_global.getFitness() << " " << best_actual.getFitness() << endl;

			fs.close();

		}


		//Funcion que almacena en un fichero una serie de datos de salida del programa
		void simpleSaveResults(const SolutionMSP &inicial, const double &best_fitness, double &tiempo, int iteraciones) {

		  string line;
		  ofstream fs;

		      fs.open("MSP_Fitness&Time.txt", std::ofstream::app);
		      if (iteraciones != 1) fs << endl;
		       fs << iteraciones << " " << inicial.getFitness() << " " << best_fitness << " " <<  tiempo <<  " " << endl;
		      fs.close();

		}

};

#endif
