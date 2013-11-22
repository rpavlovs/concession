#include <uC++.h>
#include <iostream>
#include <vector>

#include "MPRNG.h"
#include "config.h"
// #include "bank.h"
// #include "bottlingPlant.h"
// #include "nameServer.h"
// #include "parent.h"
// #include "printer.h"
// #include "student.h"
// #include "truck.h"
// #include "watcard.h"
// #include "watcardOffice.h"

using namespace std;

void usage() {
    cout << "Usage: soda [config-file] [seed > 0]" << endl;
}

#define NO_DEBUG

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

void printHeader( ConfigParms &cparms ) {

    for(int id = 0; id < configs.numStudents; id += 1) {
        cout << "Stud" << id << '\t';
    }

    for(int id = 0; id < configs.numVendingMachines; id += 1) {
        cout << "Mach" << id << '\t';
    }
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
    printHeader(configs);

        #ifdef DEBUG 
            printParams( configs ); 
        #endif

	// create printer, bank, parent, WATCard Office, name server
	Printer printer( configs.numStudents, configs.numVendingMachines, configs.numCouriers );
    Bank bank( configs.numStudents );
    Parent *parent = new Parent( printer, bank, configs.numStudents, configs.parentalDelay );
    WATCardOffice *office = new WATCardOffice( printer, bank, configs.numCouriers );
    NameServer *server = new NameServer( printer, configs.numVendingMachines, confrigs.numStudents );

    // create vending machines
    for(int id = 0; id < configs.numVendingMachines; id += 1) {
        VMList.push_back( 
            new VendingMachine( printer, *server, id, configs.sodaCost, configs.maxStockPerFlavour )
        );
    }

    // create bottling plant
    BottlingPlant *plant = new BottlingPlant( printer, *server, configs.numVendingMachines, 
            configs.maxShippedPerFlavour, configs.maxStockPerFlavour, configs.timeBetweenShipments );

    // create students
    for(int id = 0; id < configs.numStudents; id += 1) {
        studentList.push_back( new Student( printer, *server, *office, id, configs.maxPurchases ) );
    }

    // do stuff
    
    // clean up memory
		// delete bottling plant before vending machines

    for(unsigned int i = 0; i < configs.numStudents; i += 1) {
        delete studentList[i];
    }

    delete plant;
    
    for(unsigned int i = 0; i < configs.numVendingMachines; i += 1) {
        delete VMList[i];
    }

    delete server;
    delete office;
    delete parent;

    // final output
	cout << "*************************" << endl;
} // uMain::main
