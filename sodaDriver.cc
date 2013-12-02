#include <uC++.h>
#include <iostream>
#include <vector>

#include "MPRNG.h"
#include "config.h"
#include "printer.h"
#include "bank.h"
#include "parent.h"
#include "nameServer.h"
#include "vendingMachine.h"
#include "bottlingPlant.h"
#include "watcardOffice.h"
#include "student.h"

using namespace std;

void usage() {
    cout << "Usage: soda [config-file] [seed > 0]" << endl;
}

void printParams( ConfigParms &cparms ) {
    cout << "sodaCost = \t\t" << cparms.sodaCost << endl;
    cout << "numStudents = \t\t" << cparms.numStudents << endl;
    cout << "maxPurchases = \t\t" << cparms.maxPurchases << endl;
    cout << "numVendingMachines = \t" << cparms.numVendingMachines << endl;
    cout << "maxStockPerFlavour = \t" << cparms.maxStockPerFlavour << endl;
    cout << "maxShippedPerFlavour = \t" << cparms.maxShippedPerFlavour << endl;
    cout << "timeBetweenShipments = \t" << cparms.timeBetweenShipments << endl;
    cout << "parentalDelay = \t" << cparms.parentalDelay << endl;
    cout << "numCouriers = \t\t" << cparms.numCouriers << endl;
}

MPRNG randGen;

void uMain::main() {

    // config-file name and random seed
	char configFile[500];
    strcpy( configFile, "soda.config" );
    int seed = getpid();           // random seed 

    switch ( argc ) {
        case 3:     // seed > 0
            seed = atoi( argv[2] );
            if ( seed <= 0 ) {
                usage();
                return;
            }

        case 2:     // config-file name
            strcpy( configFile, argv[1] );
        case 1:
            break;
        default:
            usage();
	        return;
    } // switch

    // set up
	randGen.seed( seed );

    vector<VendingMachine*> VMList;
    vector<Student*> studentList;

    // read in configs
    ConfigParms configs;
    processConfigFile( configFile, configs );

	// create printer, bank, parent, WATCard Office, name server
    Printer prt( configs.numStudents, configs.numVendingMachines, configs.numCouriers );
    Bank bank( configs.numStudents );
    Parent *parent = new Parent( prt, bank, configs.numStudents, configs.parentalDelay );

    WATCardOffice office( prt, bank, configs.numCouriers );
    NameServer server( prt, configs.numVendingMachines, configs.numStudents );

    // create vending machines
    for(unsigned int id = 0; id < configs.numVendingMachines; id += 1) {
        VMList.push_back( 
            new VendingMachine( prt, server, id, configs.sodaCost, configs.maxStockPerFlavour )
        );
    }

    // create bottling plant
    BottlingPlant *plant = new BottlingPlant( prt, server, configs.numVendingMachines, 
            configs.maxShippedPerFlavour, configs.maxStockPerFlavour, configs.timeBetweenShipments );

    // create students
    // for(unsigned int id = 0; id < configs.numStudents; id += 1) {
    //     studentList.push_back( new Student( prt, server, office, id, configs.maxPurchases ) );
    // }

    // do stuff
    WATCard::FWATCard fwatcard = office.create( 1, 5 );
    cout << "balance " << fwatcard()->getBalance() << endl;
    delete fwatcard;
    
    // clean up memory
    
    // clean up memory

    // for(unsigned int i = 0; i < configs.numStudents; i += 1) {
    //     delete studentList[i];
    // }

    // delete bottling plant before vending machines
    delete plant;
    
    for(unsigned int i = 0; i < configs.numVendingMachines; i += 1) {
        delete VMList[i];
    }

    delete parent;

} // uMain::main






    // prt.print( Printer::NameServer, 'S' );
    // prt.print( Printer::NameServer, 'R', 0 );
    // prt.print( Printer::Student, 1, 'S', 0, 3 );
    // prt.print( Printer::NameServer, 'N', 0, 0 );
    // prt.print( Printer::NameServer, 'F' );

    // prt.print( Printer::Student, 1, 'V', 1 );
    // prt.print( Printer::Student, 1, 'F' );
    // prt.print( Printer::BottlingPlant, 'F' );


    // bank.withdraw(0, 5);
    // bank.withdraw(1, 8);
