#ifndef __VENDING_MACHINE_H__
#define __VENDING_MACHINE_H__

#include "printer.h"
#include "watcard.h"

_Task NameServer;

_Task VendingMachine {
    Printer *prt;
    unsigned int id;
    unsigned int sodaCost;
    unsigned int maxStock;
    unsigned int sodaInventory[4];

    void main();
  public:
    enum Flavours { BLACK_CHERRY, CREAM_SODA, ROOT_BEER, LIME };                 // flavours of soda (YOU DEFINE)
    enum Status { BUY, STOCK, FUNDS };     // purchase status: successful buy, out of stock, insufficient funds
    VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                    unsigned int maxStockPerFlavour );
    Status buy( Flavours flavour, WATCard &card );
    unsigned int* inventory();
    void restocked();
    _Nomutex unsigned int cost();
    _Nomutex unsigned int getId();
};

#endif
