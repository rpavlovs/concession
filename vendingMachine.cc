#include "vendingMachine.h"
#include "watcard.h"
#include "nameServer.h"
#include <iostream>

VendingMachine::VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                    unsigned int maxStockPerFlavour ) : prt(&prt), id(id), sodaCost(sodaCost), 
                    maxStock(maxStockPerFlavour) {
	nameServer.VMregister( this );
	for (int i = 0; i < 4; i += 1) {
		sodaInventory[i] = 0;
	}
	this->prt->print( Printer::Vending, id, 'S', sodaCost );
}


void
VendingMachine::main() {
	for(;;) {
		_Accept( inventory ) {
			_Accept( restocked );
		}
		or _Accept( buy );
		or _Accept( ~VendingMachine ) { break; }
	}
	prt->print( Printer::Vending, id, 'F' );
}


VendingMachine::Status
VendingMachine::buy( Flavours flavour, WATCard &card ) {
	if ( sodaInventory[flavour] == 0 ) { return STOCK; }
	if ( card.getBalance() < sodaCost )	{ return FUNDS; }

	prt->print( Printer::Vending, id, 'B', flavour, sodaInventory[flavour] );
	card.withdraw(sodaCost);
	return BUY;	
}

unsigned int *
VendingMachine::inventory() {
	prt->print( Printer::Vending, id, 'r' );
	return sodaInventory;
}

void
VendingMachine::restocked() {
	prt->print( Printer::Vending, id, 'R' );
}

unsigned int
VendingMachine::cost() {
	return sodaCost;
}

unsigned int
VendingMachine::getId() {
	return id;
}
