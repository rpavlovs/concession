#ifndef __BOTTLING_PLANT_H__
#define __BOTTLING_PLANT_H__

#include "MPRNG.h"
#include "printer.h"
#include "nameServer.h"

extern MPRNG randGen;

_Task BottlingPlant {
	Printer *prt;
	NameServer *nameServer;
	unsigned int numVMs;
	unsigned int maxShipped;
	unsigned int maxStock;
	unsigned int timeBetweenShipments;
	bool closingDown;
	unsigned int inventory[4];

	void produceSoda();
    void main();
  public:
    BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
                 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                 unsigned int timeBetweenShipments );
    bool getShipment( unsigned int cargo[] );
};

#endif
