#include <iostream>
using namespace std;

#include "printer.h"

#define WITH_DOTS true

Printer::Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers ) :
				num( {numStudents, numVendingMachines, numCouriers} ),
				lidStates( {new State[numStudents], new State[numVendingMachines], new State[numCouriers]} ) {
	unsigned int lid, i;
	cout << "Parent\tWATOff\tNames\tTruck\tPlant";
	for (lid = 0; lid < numStudents; ++lid)
		cout << "\tStud" << lid;
	for (lid = 0; lid < numVendingMachines; ++lid)
		cout << "\tMach" << lid;
	for (lid = 0; lid < numCouriers; ++lid)
		cout << "\tCour" << lid;
	cout << "\n*******";
	for ( i = 1; i < 5 + numStudents + numVendingMachines + numCouriers; i++ )
		cout << "\t*******";
	cout << endl;
}

Printer::~Printer() {
	flush( ! WITH_DOTS );
	for (int i = 0; i < 3; ++i)
		delete[] lidStates[i];
	cout << "***********************" << endl;
}

void
Printer::State::print( bool withDots ) {
	if ( isWritten ) {
		cout << state;
		if ( intOne != -1 )	cout << intOne;
		if ( intTwo != -1 )	cout << "," << intTwo;
		isWritten = false;
	}
	else {
		cout << ( withDots ? "..." : "   ");
	}
}

void
Printer::State::set( char s ) {
	isWritten = true;
	state = s;
	intOne = -1;
	intTwo = -1;
}

void
Printer::State::set( char s, int i1 ) {
	isWritten = true;
	state = s;
	intOne = i1;
	intTwo = -1;
}

void
Printer::State::set( char s, int i1, int i2 ) {
	isWritten = true;
	state = s;
	intOne = i1;
	intTwo = i2;
}

bool
Printer::isRowBufEmpty() {
	unsigned int i, uidObj;
	for (i = 0; i < 5; ++i) {
		if ( nonlidStates[i].isWritten ) return false;
	}
	for (uidObj = 0; uidObj < 3; ++uidObj) {
		for ( i = 0; i < num[uidObj]; ++i ) {
			if ( lidStates[uidObj][i].isWritten ) return false;
		}
	}
	return true;
}

void
Printer::flush( bool withDots ) {
	unsigned int i, uid, uidObj;
	if ( isRowBufEmpty() ) return;	

	i = 0;
	for (;;) {
		nonlidStates[i].print( withDots );
		if ( ++i == 5 ) break;
		cout << "\t";
	}
	for ( uidObj = 0; uidObj < 3; ++uidObj ) {
		for ( uid = 0; uid < num[uidObj]; ++uid ) {
			cout << "\t";
			lidStates[uidObj][uid].print( withDots );		
		}
	}
	cout << endl;
}

void 
Printer::print( Kind kind, char state ) {
	if ( nonlidStates[kind].isWritten || state == 'F' ) flush( ! WITH_DOTS );
	nonlidStates[kind].set( state );
	if ( state == 'F' ) flush( WITH_DOTS );
}

void 
Printer::print( Kind kind, char state, int value1 ) {
	if ( nonlidStates[kind].isWritten || state == 'F' ) flush( ! WITH_DOTS );
	nonlidStates[kind].set( state, value1 );
	if ( state == 'F' ) flush( WITH_DOTS );
}

void 
Printer::print( Kind kind, char state, int value1, int value2 ) {
	if ( nonlidStates[kind].isWritten || state == 'F' ) flush( ! WITH_DOTS );
	nonlidStates[kind].set( state, value1, value2 );
	if ( state == 'F' ) flush( WITH_DOTS );
}

void 
Printer::print( Kind kind, unsigned int lid, char state ) {
	if ( lidStates[INDEX(kind)][lid].isWritten || state == 'F' ) flush( ! WITH_DOTS );
	lidStates[INDEX(kind)][lid].set( state );
	if ( state == 'F' ) flush( WITH_DOTS );
}

void 
Printer::print( Kind kind, unsigned int lid, char state, int value1 ) {
	if ( lidStates[INDEX(kind)][lid].isWritten || state == 'F' ) flush( ! WITH_DOTS );
	lidStates[INDEX(kind)][lid].set( state, value1 );
	if ( state == 'F' ) flush( WITH_DOTS );
}

void 
Printer::print( Kind kind, unsigned int lid, char state, int value1, int value2 ) {
	if ( lidStates[INDEX(kind)][lid].isWritten || state == 'F' ) flush( ! WITH_DOTS );
	lidStates[INDEX(kind)][lid].set( state, value1, value2 );
	if ( state == 'F' ) flush( WITH_DOTS );
}

