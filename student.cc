#include "student.h"
#include "watcardOffice.h"

#define WATCARD_INITIAL_BALANCE 5

Student::Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice,
			unsigned int id, unsigned int maxPurchases ) : prt(&prt), nameServer(&nameServer),
			cardOffice(&cardOffice), id(id), numPurchases(randGen(1,maxPurchases)),
			favFlavour((VendingMachine::Flavours)randGen(0,3)) {
	fwatcard = cardOffice.create( id, WATCARD_INITIAL_BALANCE );
	prt.print( Printer::Student, id, 'S', favFlavour, numPurchases );
	machine = nameServer.getMachine( id );
	prt.print( Printer::Student, id, 'V', machine->getId() );
}

Student::~Student() {
	delete fwatcard;
}

void
Student::main() {
	VendingMachine::Status st;
	while ( numPurchases != 0 ) {
		yield( randGen(1,10) );
		while(1) {
			try {			
				st = machine->buy( favFlavour, *fwatcard() );

				if ( st == VendingMachine::FUNDS ) {
					fwatcard = cardOffice->transfer( id, machine->cost() + 5, fwatcard() );
				}
				if ( st == VendingMachine::STOCK ) {
					machine = nameServer->getMachine( id );
				}
				if ( st == VendingMachine::BUY ) break;
			} catch( WATCardOffice::Lost ) {
				prt->print( Printer::Student, id, 'L' );
				fwatcard = cardOffice->create( id, WATCARD_INITIAL_BALANCE );
			}
		}
		prt->print( Printer::Student, id, 'B', fwatcard()->getBalance() );
		numPurchases--;
	}
	prt->print( Printer::Student, id, 'F' );
}