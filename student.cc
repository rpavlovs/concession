#include "student.h"
#include "MPRNG.h"

MPRNG rnd;

#define WATCARD_INITIAL_BALANCE 5

Student::Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice,
			unsigned int id, unsigned int maxPurchases ) : prt(&prt), nameServer(&nameServer),
			cardOffice(&cardOffice), id(id), numPurchases(rnd(1,maxPurchases)),
			favFlavour(rnd(1,3)) {
	// fwatcard = cardOffice.create( id, WATCARD_INITIAL_BALANCE );
	machine = nameServer.getMachine( id );
	prt.print( Printer::Student, id, 'S', favFlavour, numPurchases );
}

Student::~Student() {
	prt->print( Printer::Student, id, 'F' );
}

void
Student::main() {
	while ( numPurchases != 0 ) {
		yield( rnd(1,10) );
		machine->buy( favFlavour, watcard )

		numPurchases--;
	}
}