#ifndef __INSTANCE_HPP__
#define __INSTANCE_HPP__

#include <fstream>
#include <iostream>
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


		Instance(const string &file_name, char separator = ' '){

			_separator = separator;
			_file_name = file_name;
		}


		~Instance(){

			if(_file.is_open())
				_file.close();
		}


		int getVariableNumber(){return _var_number;};
		int getClauseNumber(){return _cla_number;}


		//Funcion para leer una instancia determinada de el fichero csv
		bool load_instance(vector< vector <int> > &clauses){

			_file.open(_file_name);

			if(not _file.is_open()) {

				std::cerr << "El fichero no se pudo abrir." << std::endl;
				return false;
			}

			clauses = load();

		  return true;
		}



		//Loads the current instance pointed by the file pointer
		vector < vector <int> > load() {

		  vector < vector <int> > instance;
		  vector <int> aux;
		  string value;
		  int cont = 0;	

			if(not _file.is_open()) {
				std::cerr << "El fichero esta cerrado." << endl;
				exit(-1);
			}


			header();	//Nos saltamos la cabecera


			while(getline(_file, value, _separator)) {

				//Obnetemos las diferentes variables de las clausulas
				while(atoi(value.c_str()) != 0){

					aux.push_back( atoi(value.c_str()) );
					getline(_file, value, _separator);
				}

				getline(_file, value, '\n');	//Necesario para pasar a la siguiente linea ??

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

		  string line;
		  char c = ' ';

			//Extraemos todas las lineas introductorias de la instancia

			getline(_file, line, _separator);
			c = line[0];
			while(c == 'c'){

				getline(_file, line, '\n');
				getline(_file, line, _separator);
				c = line[0];
			}


			//Obtenemos el tamaño del problema de la linea que comienza por 'p'

//			getline(_file, line, _separator);	// 'p'
			getline(_file, line, _separator);	// "cnf"

			getline(_file, line, _separator);
			_var_number = atoi(line.c_str());			//Obtenemos el numero de variables

			getline(_file, line, '\n');
			_cla_number = atoi(line.c_str());			//Obtenemos el numero de clausulas
		}



};

#endif
