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


		//Funcion para leer una instancia determinada de el fichero csv
		bool load_instance(vector< vector <int> > &clauses){

			_file.open(_file_name);

			if(not _file.is_open()) {

				std::cerr << "El fichero no se pudo abrir." << std::endl;
				return false;
			}

			instance = load();

		  return true;
		}



		//Loads the current instance pointed by the file pointer
		vector < vector <int> > load() {

		  vector < vector <int> > instance;
		  vector <int> aux;
		  string value;
		  int cont = 0;	

			if(not _file.is_open()) {
				std::cerr << "El fichero esta cerrado." << std::endl;
				exit(-1);
			}


			header();	//Nos saltamos la cabecera


			while(getline(_file, value, _separator)) {

				//Obnetemos las diferentes variables de las clausulas
				while(stoi(value) != 0){

					aux.push_back( stoi(value) )
					getline(_file, value, _separator);
				}

				//getline(_file, value, '\n');	//Necesario para pasar a la siguiente linea ??

				instance.push_back(aux);
			}

			return instance;
		}




		//Si store esta a true se guarda el contenido de la cabecera en el vector _header
		void header() {

			if(not _file.is_open()) {

				std::cerr << "El fichero esta cerrado." << std::endl;
				return false;
			}

		  string line;
		  char c;

			//Extraemos todas las lineas introductorias de la instancia
			while(c != 'c'){

				getline(_file, line, '\n');
				c = line[0];
			}

			getline(_file, line, '\n');	//Nos saltamos la linea que empieza por 'p'

		}



};

#endif
