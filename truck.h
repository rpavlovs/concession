#ifndef __TRUCK_H__
#define __TRUCK_H__

#include "MPRNG.h"
#include "printer.h"
#include "nameServer.h"
#include "bottlingPlant.h"

extern MPRNG randGen;

_Task Truck {
	Printer *prt;
	NameServer *nameServer;
	BottlingPlant *plant;

	unsigned int numVMs;
	unsigned int maxStock;
	unsigned int deliveryStock[4];
	VendingMachine **VMs;

    void main();
    void restock();

  public:
    Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
           unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
};

#endif
