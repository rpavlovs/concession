#include "truck.h"


Truck::Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
           unsigned int numVendingMachines, unsigned int maxStockPerFlavour ) :
           prt(&prt), nameServer(&nameServer), plant(&plant), numVMs(numVendingMachines), 
           maxStock(maxStockPerFlavour) {

    for(int i = 0; i < 4; i += 1) {
    	deliveryStock[i] = 0;
    }

	VMs = nameServer.getMachineList();
	prt.print( Printer::Truck, 'S' );
}

void Truck::main() {
	for(;;) {
		yield( randGen(1, 10) );
		bool closing = plant->getShipment( deliveryStock );

		if ( closing ) { break; }

		unsigned int stock = countInventory( deliveryStock );
		prt->print( Printer::Truck, 'P', stock );

		restock(stock);	
	}
	prt->print( Printer::Truck, 'F' );	
}

void Truck::restock( int stockRemaining ) {
	unsigned int maxInventory = maxStock * 4;

	for(unsigned int i = 0; i < numVMs && stockRemaining > 0; i += 1) {
		// begin delivery to vending machine
		prt->print( Printer::Truck, 'd', VMs[i]->getId(), stockRemaining );
		
		unsigned int* vmInventoryList = VMs[i]->inventory();
		unsigned int vmInventoryCount = 0;

		// restock each flavour
		for(int j = 0; j < 4; j += 1) {
			unsigned int vmInventorySpace = maxStock - vmInventoryList[j];

			// space for that soda in VM, and truck has that soda
			if ( vmInventoryList[j] < maxStock && deliveryStock[j] > 0 ) {
				// truck can fully stock VM
				if ( deliveryStock[j] >= vmInventorySpace ) {
					vmInventoryList[j] += vmInventorySpace;
					deliveryStock[j] -= vmInventorySpace;

					// reduce truck's total stock
					stockRemaining -= vmInventorySpace;
				}
				// VM cannot be fully stocked
				else {
					vmInventoryList[j] += deliveryStock[j];
					// reduce truck's total stock
					stockRemaining -= deliveryStock[j];
					deliveryStock[j] = 0;
				}
			}
			// add up stock of vending machine
			vmInventoryCount += vmInventoryList[j];
		} // for each flavour

		if ( maxInventory - vmInventoryCount > 0 ) {
			prt->print( Printer::Truck, 'U', VMs[i]->getId(), maxInventory - vmInventoryCount );
		}

		VMs[i]->restocked();
		prt->print( Printer::Truck, 'D', VMs[i]->getId(), stockRemaining );
	} // for each vending machine
} // restock

unsigned int Truck::countInventory( unsigned int * inventoryList ) {

	unsigned int stock;
	for (int i = 0; i < 4; i += 1) {
		stock += inventoryList[i];
	}
	return stock;	
}
