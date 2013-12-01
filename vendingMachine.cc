#include "vendingMachine.h"
#include "watcard.h"
#include "nameServer.h"

VendingMachine::VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                    unsigned int maxStockPerFlavour ) : prt(&prt), id(id), sodaCost(sodaCost), 
                    maxStock(maxStockPerFlavour) {
	nameServer.VMregister( this );
	for (int i = 0; i < 4; i += 1) {
		sodaInventory[i] = 0;
	}
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
}


VendingMachine::Status
VendingMachine::buy( Flavours flavour, WATCard &card ) {
	if ( sodaInventory[flavour] == 0 ) { return STOCK; }
	if ( card.getBalance() < sodaCost )	{ return FUNDS; }

	card.withdraw(sodaCost);
	return BUY;	
}

unsigned int *
VendingMachine::inventory() {
	return sodaInventory;
}

void
VendingMachine::restocked() {

}

unsigned int
VendingMachine::cost() {
	return sodaCost;
}

unsigned int
VendingMachine::getId() {
	return id;
}
