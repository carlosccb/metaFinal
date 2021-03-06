#ifndef __MISCELANEA_HPP__
#define __MISCELANEA_HPP__

#include <iostream>
#include <list>
#include <string>
#include <vector>

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
