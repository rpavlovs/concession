#include "truck.h"

Truck::Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
           unsigned int numVendingMachines, unsigned int maxStockPerFlavour ) :
           prt(&prt), nameServer(&nameServer), plant(&plant), numVMs(numVendingMachines), 
           maxStock(maxStockPerFlavour) {

    for(int i = 0; i < 4; i += 1) {
    	deliveryStock[i] = 0;
    }

	VMs = nameServer.getMachineList();
}

void Truck::main() {
	yield( randGen(1, 10) );
	bool closing = plant->getShipment( deliveryStock );

	if ( closing ) { return; }
	restock();
}

void Truck::restock() {
	for(unsigned int i = 0; i < numVMs; i += 1) {
		unsigned int* inventory = VMs[i]->inventory();

		for(int j = 0; j < 4; j += 1) {
			unsigned int stockRoom = maxStock - inventory[j];

			// space for that soda in VM, and truck has that soda
			if ( inventory[j] < maxStock && deliveryStock[j] > 0 ) {
				// truck can fully stock VM
				if ( deliveryStock[j] >= stockRoom ) {
					inventory[j] += stockRoom;
					deliveryStock[j] -= stockRoom;
				}
				// VM cannot be fully stocked
				else {
					inventory[j] += deliveryStock[j];
					deliveryStock[j] = 0;
				}
			}
		} // for deliveryStock
	} // for vending machines
} // restock
