#ifndef __NAME_SERVER_H__
#define __NAME_SERVER_H__

#include "printer.h"
#include "vendingMachine.h"

_Task NameServer {
	Printer *prt;
	unsigned int numVendingMachines, numStudents, nextMachineId;
	VendingMachine **machines;
	int *studToMachneId;
    void main();
  public:
    NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents );
    ~NameServer();
    void VMregister( VendingMachine *vendingmachine );
    VendingMachine *getMachine( unsigned int id );
    VendingMachine **getMachineList();
};

#endif
