#ifndef __MISCELANEA_HPP__
#define __MISCELANEA_HPP__

#include <iostream>
#include <list>
#include <string>
#include <vector>

struct problem_element {
	int clausula1; 
	int clausula2; 
	int clausula3;

	/***********************************************************/
	/* --------------- TODO -----------------------------------*/
	/*  ATENCION: ESTO ESTA PARA QUITAR ERRORES
	 * NO FUNCIONA ASI. NO HAY DOS MIEMBROS EN ESTA ESTRUCTURA */
	int a;
	int b;

	/***********************************************************/

};

void printVect(const std::vector<int> &v, std::string separator="", bool endLine=true);

void printList(const std::list<int> &v, std::string separator="", bool endLine=true);

template<class T>
void printArray(const T &v, std::string separator="", bool endLine=true){
	for(auto i: v)
		std::cout << i << separator;
	if(endLine)
		std::cout << std::endl;
}

#endif
