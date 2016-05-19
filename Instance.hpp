#ifndef __INSTANCE_HPP__
#define __INSTANCE_HPP__

#include <fstream>
#include <iostream>
#include <limits>
#include <regex>
#include <string>
#include <vector>

#include "Miscelanea.hpp"

class Instance {
	protected:
		std::fstream _file;

		std::string _file_name;
		unsigned int _header_lines;
		//Line that contains the length of one specific instance
		unsigned int _length_line;
		unsigned int _instance_length;
		//value separator
		char _separator;
		//Number of lines between two instances
		unsigned int _end_lines;

		//Stores all the header lines of a given instance
		std::vector<std::string> _header;

	public:
		Instance() {}
		Instance(std::string file_name, unsigned int header_lines, unsigned int length_line, char separator, unsigned int end_lines = 0) 
			: _file_name(file_name), _header_lines(header_lines), _length_line(length_line), _end_lines(end_lines)
		{
			_separator = separator;
		}

		~Instance() {
			if(_file.is_open())
				_file.close();
		}

		//Funcion para leer una instancia determinada de el fichero csv
		bool load_instance(std::vector<problem_element> &instance, int desired_instance=1);

		std::vector<std::string> getHeader();
		std::string getHeader(unsigned int n);

	//Estas funciones solo son accesibles desde dentro de la clase o de clases que hereden
	protected:
		//Si store esta a true se guarda el contenido de la cabecera en el vector _header
		bool header(bool store=false);


		//Skips n instances
		bool skip(unsigned int n);

		//Loads the current instance pointed by the file pointer
		std::vector<problem_element> load();
};

#endif
