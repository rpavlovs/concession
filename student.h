#ifndef __STUDENT_H__
#define __STUDENT_H__

#include "printer.h"
#include "nameServer.h"
#include "watcard.h"
#include "watcardOffice.h"

_Task Student {
	Printer *prt;
	NameServer *nameServer;
	WATCardOffice *cardOffice;
	WATCard::FWATCard fwatcard;
	int id, numPurchases;
	VendingMachine *machine;
	VendingMachine::Flavours favFlavour;
    void main();
  public:
    Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice,
    		unsigned int id, unsigned int maxPurchases );
    ~Student();
};

#endif
