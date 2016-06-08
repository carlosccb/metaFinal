#ifndef __INSTANCE_HPP__
#define __INSTANCE_HPP__

#include <fstream>
#include <iostream>
#include <sstream>
#include <limits>
#include <regex>
#include <string>
#include <vector>

#include "Miscelanea.hpp"

using namespace std;


class Instance {

	private:
		fstream _file;

		string _file_name;
		char _separator;	//value separator

		int _var_number;
		int _cla_number;


	public:
		Instance(){};

		Instance(const string &file_name, char separator = ' ') {
			_separator = separator;
			_file_name = file_name;
		}

		~Instance(){
			if(_file.is_open())
				_file.close();
		}

		int getVariableNumber() {return _var_number;};
		int getClauseNumber() {return _cla_number;}


		//Funcion para leer una instancia determinada de el fichero csv
		bool load_instance(vector<vector<int>> &clauses){
			_file.open(_file_name);

			if(not _file.is_open()) {
				std::cerr << "El fichero no se pudo abrir." << std::endl;
				return false;
			}

			clauses = load();

		  return true;
		}

		//Loads the current instance pointed by the file pointer
		vector<vector<int>> load() {

		  vector<vector<int>> instance;
		  vector <int> aux;
		  string line;
		  int num;	


			header();	//Nos saltamos la cabecera

			//Cargamos la instancia
			while(getline(_file, line)){

			  istringstream isaux(line);

				isaux >> num;
				while(num != 0){

					aux.push_back(num);
					isaux >> num;
				}

				instance.push_back(aux);
				aux.clear();
			}



			return instance;
		}




		//Si store esta a true se guarda el contenido de la cabecera en el vector _header
		void header() {

			if(not _file.is_open()) {

				std::cerr << "El fichero esta cerrado." << endl;
				return;
			}

		  string line, p;

			//Leemos las lineas con comentarios
			getline(_file, line);
			while(line[0] == 'c')
				getline(_file, line);


			//Llegamos a la linea con p
			if(line[0] != 'p'){

				cout << endl << "¡¿Que esta pasando?!" << endl << endl;
				exit(0);
			}

		  istringstream isnumbers(line);

			isnumbers >> p;	//p
			isnumbers >> p;	//cnf

			isnumbers >> _var_number;
			isnumbers >> _cla_number;

		}



};

#endif
