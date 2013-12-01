#include "bottlingPlant.h"
#include "printer.h"
#include "truck.h"


BottlingPlant::BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
                 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                 unsigned int timeBetweenShipments ) : prt(&prt), nameServer(&nameServer), 
                 numVMs(numVendingMachines), maxShipped(maxShippedPerFlavour), maxStock(maxStockPerFlavour),
                 timeBetweenShipments(timeBetweenShipments) {

    closingDown = false;

	for(int i = 0; i < 4; i += 1) {
		inventory[i] += 0;
	}

}

void BottlingPlant::main() {
	for(;;) {
		_Accept( ~BottlingPlant ) {
			closingDown = true;
			// bottling plant is closing, so let Truck find out
			_Accept( getShipment );
			break;
		}
		_Else {
			produceSoda();
			_Accept( getShipment );
		}
	}
}

void BottlingPlant::produceSoda() {
	yield( timeBetweenShipments );

	for(int i = 0; i < 4; i += 1) {
		inventory[i] += randGen( maxShipped );
	}
}

bool BottlingPlant::getShipment( unsigned int cargo[] ) {
	if ( closingDown ) { return true; }

	std::copy( inventory, inventory + 4, cargo );
	return false;
}
