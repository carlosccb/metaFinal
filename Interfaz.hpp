#ifndef __INTERFAZ_HPP__
#define __INTERFAZ_HPP__

#include <iostream>
#include <vector>

#include "Instance.hpp"
#include "InstanceMSP.hpp"

using namespace std;

class Interfaz {

	private:

		int opt;
		string fileName;
		
		int _variables;
		int _clauses;
		

	public:

		Interfaz() {}
		~Interfaz() {}

		//Observadores
		string getFileName(){ return fileName;};

		int getVariablesNumber() {return _variables;}
		int getClausesNumber() {return _clauses;}

		int option_menu() {

			do {

				cout << "\n\n";
				cout << "¿Que metaheuristica deseas ejecutar?: " << endl << endl;

				cout << "  0. Exit" << endl;
				cout << "  1. Busqueda Aleatoria" << endl;
				cout << "  2. Busqueda Local" << endl;
				cout << "  3. Enfriamiento Simulado" << endl;
				cout << "  4. GRASP" << endl;
				cout << "  5. Algoritmo Genetico" << endl;

				cout << endl << "Opcion: ";
				cin >> opt;


			} while(0 > opt || opt > 5);

			cout << endl << "__________________________" << endl << endl;

		  return opt;

		}

		int getOpt() {return opt;}


		vector < vector <int> > read_instance(){

		  vector <vector <int> > inst_v;
		  bool ret = false;

			while(not ret) {

				//Obtenemos el nombre del fichero
				string fileName;
				cout << "Introduzca el nombre del fichero: ";
				cin >> fileName;
				fileName =  "instances/" + fileName;

				//Cargamos la instancia
				InstanceMSP inst(fileName);
				ret = inst.load_instance(inst_v);

				_variables = inst.getVariableNumber();
				_clauses = inst.getClauseNumber();

				if(not ret)
					std::cerr << "ERROR: El fichero no se pudo abrir.\n";

			}


			return inst_v;
		}


/*
		void print_instance(std::vector<problem_element> &inst_v) {
				std::cout << "\nInstancia :\n";// << instance.inst_num << " de " << instance.fileName << endl;
				for(unsigned int i = 0; i < inst_v.size(); i++)
					std::cout << inst_v[i].id << ": \n  a: " << inst_v[i].a << "\n  b: " << inst_v[i].b << std::endl;
		}
*/
};

#endif