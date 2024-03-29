#include "bottlingPlant.h"
#include "printer.h"
#include "truck.h"

#include <iostream>

BottlingPlant::BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
                 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                 unsigned int timeBetweenShipments ) : prt(&prt), nameServer(&nameServer), 
                 numVMs(numVendingMachines), maxShipped(maxShippedPerFlavour), maxStock(maxStockPerFlavour),
                 timeBetweenShipments(timeBetweenShipments) {

    closingDown = false;

	for(int i = 0; i < 5; i += 1) {
		inventory[i] = 0;
	}
	prt.print( Printer::BottlingPlant, 'S' );

	truck = new Truck( prt, nameServer, *this, numVendingMachines, maxStockPerFlavour );
}

BottlingPlant::~BottlingPlant() {
	delete truck;
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
	prt->print( Printer::BottlingPlant, 'F' );
}

void BottlingPlant::produceSoda() {
	yield( timeBetweenShipments );
	unsigned int totalBottles = 0;

	for(int i = 0; i < 4; i += 1) {
		// generate random production
		unsigned int bottles = randGen( maxShipped );

		inventory[i] = bottles;
		totalBottles += bottles;
	}
	inventory[4] = totalBottles;
	prt->print( Printer::BottlingPlant, 'G', totalBottles );
}

bool BottlingPlant::getShipment( unsigned int cargo[] ) {
	if ( closingDown ) { return true; }

	prt->print( Printer::BottlingPlant, 'P' );

	// copy production run into truck
	std::copy( inventory, inventory + 5, cargo );
	// for (int i = 0; i < 5; i +=1) {
	// 	cargo[i] = inventory[i];
	// }
	return false;
}
