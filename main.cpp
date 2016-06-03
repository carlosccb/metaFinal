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
#include "TabuSearch.hpp"
#include "TabuNeighExplorator.hpp"
#include "geneticAlgorithmMSP.hpp"

#include "funciones.hpp"

#include <iostream>
#include <vector>

using namespace std;

int main() {

	Interfaz interfaz;

	vector<vector<int>> clauses;
	int opcion;

	srand(time(NULL));

	do {

		opcion = interfaz.option_menu();

		if(opcion)
			clauses = interfaz.read_instance();

		switch(opcion){

			case 1:
				
				busquedaAleatoria(clauses, interfaz.getVariablesNumber(), interfaz.getClausesNumber());

			break;

			case 2:

				//Se ha elegido primera mejora
				if(interfaz.getOptLS() == 1){

				  neighborOperatorMSP operador(clauses);
				  firstImprovementMSP explorador(operador);
				  localSearchMSP LS(operador, explorador);

					busquedaLocal(LS, interfaz.getVariablesNumber(), interfaz.getClausesNumber());

				}

				//Se ha escogido mejor mejora
				else{


				  neighborOperatorMSP operador(clauses);
				  bestImprovementMSP explorador(operador);
				  localSearchMSP LS(operador, explorador);

					busquedaLocal(LS, interfaz.getVariablesNumber(), interfaz.getClausesNumber());

				}

			break;

			case 3:

				enfriamientoSimulado(clauses, interfaz.getVariablesNumber(), interfaz.getClausesNumber());

			break;

			case 4:
				TabuSearchMain(clauses, interfaz.getVariablesNumber(), interfaz.getClausesNumber());
				break;

			case 5:
				GRASPexplorator(clauses, interfaz.getVariablesNumber(), interfaz.getClausesNumber());
				break;

			case 6:
				algoritmoGenetico(clauses, interfaz.getVariablesNumber(), interfaz.getClausesNumber());
				break;

			case 0:
			
				cout << "Saliendo" << endl << endl;

			break;
		}

	} while (opcion);


	return 0;
}
