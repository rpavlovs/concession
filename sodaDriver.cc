#include <uC++.h>

#include <iostream>

#include "bank.h"
#include "bottlingPlant.h"
#include "config.h"
#include "nameServer.h"
#include "parent.h"
#include "printer.h"
#include "student.h"
#include "truck.h"
#include "watcard.h"
#include "watcardOffice.h"
#include "MPRNG.h"

using namespace std;

void usage() {
    cout << "Usage: soda [config-file] [seed > 0]" << endl;
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

	// create printer, bank, parent, WATCard Office, name server, vending machines, 
	// bottling plant, students
	// Printer printer();

    // do stuff
    
    // clean up memory
		// delete bottling plant before vending machines


    // final output
	cout << "*************************" << endl;
} // uMain::main
