#include <uC++.h>
#include <iostream>

#include "MPRNG.h"
#include "config.h"
#include "printer.h"
// #include "bank.h"
// #include "bottlingPlant.h"
// #include "nameServer.h"
// #include "parent.h"
// #include "student.h"
// #include "truck.h"
// #include "watcard.h"
// #include "watcardOffice.h"

using namespace std;

void usage() {
    cout << "Usage: soda [config-file] [seed > 0]" << endl;
}

// #define DEBUG

void printParams(ConfigParms &cparms) {
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
    strcpy(configFile, "soda.config");
    int seed = getpid();           // random seed 

    switch (argc) {
        case 3:     // seed > 0
            seed = atoi(argv[2]);
            if (seed <= 0) {
                usage();
                return;
            }

        case 2:     // config-file name
            strcpy(configFile, argv[1]);
        case 1:
            break;
        default:
            usage();
	        return;
    } // switch

    // set up
	randGen.seed(seed);

    ConfigParms configs;

    processConfigFile(configFile, configs);
    #ifdef DEBUG 
        printParams(configs); 
    #endif

    Printer prt( configs.numStudents, configs.numVendingMachines, configs.numCouriers );

	// create bank, parent, WATCard Office, name server, vending machines, 
	// bottling plant, students
	// Printer printer();

    // do stuff
    
    // clean up memory
		// delete bottling plant before vending machines


} // uMain::main
