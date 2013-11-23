#include "vendingMachine.h"
#include "nameServer.h"

VendingMachine::VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                    unsigned int maxStockPerFlavour ) : prt(&prt), id(id) {
	nameServer.VMregister( this );
}


void
VendingMachine::main() {

}


VendingMachine::Status
VendingMachine::buy( Flavours flavour, WATCard &card ) {

}

unsigned int *
VendingMachine::inventory() {
	return 0;
}

void
VendingMachine::restocked() {

}

unsigned int
VendingMachine::cost() {
	return 0;
}

unsigned int
VendingMachine::getId() {
	return id;
}
