#include "Interfaz.hpp"
#include "Instance.hpp"
#include "InstanceMSP.hpp"

#include "SolutionMSP.hpp"
#include "SolGeneratorMSP.hpp"
#include "neighborOperatorMSP.hpp"
#include "neighborExploratorMSP.hpp"
#include "localSearchMSP.hpp"
#include "coolingExploratorMSP.hpp"
#include "GRASPExploratorMSP.hpp"
//#include "geneticAlgorithmMSP.hpp"

#include "funciones.hpp"

#include <iostream>
#include <vector>

using namespace std;



int main() {
	

  Interfaz interfaz;

  vector < vector <int> > clauses;
  int opcion;


	opcion = interfaz.option_menu();
	clauses = interfaz.read_instance();


	switch(opcion){


		case 1:

			busquedaAleatoria(clauses, interfaz.getVariablesNumber(), interfaz.getClausesNumber());

		break;





	}


	return 0;
}
