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
//#include "geneticAlgorithmMSP.hpp"

#include "funciones.hpp"

#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char **argv) {
	int opcion;
	Interfaz interfaz;
	vector<vector<int>> clauses;

	srand(time(NULL));

	if(argc >= 3) {
		clauses = interfaz.read_instance(argv[1]);
		opcion = atoi(argv[2]);
	} else {
		cout << " # ERROR:" << endl;
		cout << " #  Se han introducido menos parametros de los necesarios para la ejecucion de este main." << endl;
		cout << " #  Usage: " << argv[0] << " fichero_de_instancias algoritmo " << endl;
		return -1;
	}

	switch(opcion) {
		case 1:			
			busquedaAleatoria(clauses, interfaz.getVariablesNumber(), interfaz.getClausesNumber());
			break;

		case 2:
			//Se ha elegido primera mejora
			if(interfaz.getOptLS() == 1) {
			  neighborOperatorMSP operador(clauses);
			  firstImprovementMSP explorador(operador);
			  localSearchMSP LS(operador, explorador);

				busquedaLocal(LS, interfaz.getVariablesNumber(), interfaz.getClausesNumber());
			} else{
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

		case 0:		
			cout << "Saliendo" << endl << endl;
			break;
	}

	return 0;
}
