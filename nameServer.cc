#include "nameServer.h"
#include "printer.h"

NameServer::NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents ) :
			prt(&prt), numVendingMachines(numVendingMachines), numStudents(numStudents), nextMachineId(0),
			machines( new VendingMachine*[numVendingMachines] ), studToMachneId( new int[numStudents] ) {
	prt.print( Printer::NameServer, 'S' );
	for (unsigned int i = 0; i < numStudents; ++i) {
		studToMachneId[i] = -1;
	}
}

NameServer::~NameServer() {
	delete[] machines;
	delete[] studToMachneId;
	prt->print( Printer::NameServer, 'F' );
}

void
NameServer::main() {

}

void
NameServer::VMregister( VendingMachine *vendingmachine ) {
	prt->print( Printer::NameServer, 'R', vendingmachine->getId() );
	machines[nextMachineId++] = vendingmachine;
}

VendingMachine*
NameServer::getMachine( unsigned int id ) {
	studToMachneId[id] = (studToMachneId[id] == -1 ? id : studToMachneId[id] + 1) % numVendingMachines;
	prt->print( Printer::NameServer, 'N', id, machines[studToMachneId[id]]->getId() );
	return machines[studToMachneId[id]];
}

VendingMachine**
NameServer::getMachineList() {
	return machines;
}