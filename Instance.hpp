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
		vector<string> _header;		//Stores all the header lines of a given instance
		int _header_lines;

		char _separator;	//value separator


	public:

		Instance(){};


		Instance(const string &file_name, char separator = ' ', int header_lines = 3){

			_separator = separator;
			_file_name = file_name;
			_header_lines = header_lines;
		}


		~Instance(){

			if(_file.is_open())
				_file.close();
		}


		//Funcion para leer una instancia determinada de el fichero csv
		bool load_instance(vector<problem_element> &instance){

			_file.open(_file_name);

			if(not _file.is_open()) {

				std::cerr << "El fichero no se pudo abrir." << std::endl;
				return false;
			}

			instance = load();

		  return true;
		}



		//Si store esta a true se guarda el contenido de la cabecera en el vector _header
		bool header(bool store = false){


			if(not _file.is_open()){

				std::cerr << "El fichero esta cerrado." << endl;
				return false;
			}

			for(unsigned int i = 0; i < _header_lines; i++) {

			  string line;

				getline(_file, line);

				if(store)
					_header.push_back(line);
/*
				if(i == _length_line) {

					const std::string c_line = line;
					regex rgx(".* (\\d+) *$");
					smatch match;

					if (regex_search(c_line.begin(), c_line.end(), match, rgx))
						_instance_length = stoi(match[1]);

					else {

						std::cerr << "No se encontro longitud de la instancia en la cabecera del fichero." << endl;
						exit(-1);
					}
				}
*/
			}
		}






};

#endif
