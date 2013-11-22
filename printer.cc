#include <iostream>

using namespace std;

#include "printer.h"


Printer::Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers ) :
				num[INDEX(Printer::Student)]( numStudents ),
				num[INDEX(Printer::Vending)]( numVendingMachines ),
				num[INDEX(Printer::Courier)]( numCouriers ),
				states[INDEX(Printer::Student)]( new State[numStudents] ),
				states[INDEX(Printer::Vending)]( new State[numVendingMachines] ),
				states[INDEX(Printer::Courier)]( new State[numCouriers] ) {

}

Printer::~Printer() {
	for (int i = 0; i < 3; ++i)
		delete[] states[i];
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
Printer::State::operator()( char s ) {
	isWritten = true;
	state = s;
	intOne = -1;
	intTwo = -1;
}

void
Printer::State::operator()( char s, int i1 ) {
	isWritten = true;
	state = s;
	intOne = i1;
	intTwo = -1;
}

void
Printer::State::operator()( char s, int i1, int i2 ) {
	isWritten = true;
	state = s;
	intOne = i1;
	intTwo = i2;
}

bool
Printer::isRowBufEmpty() {
	unsigned int i, uidObj;
	for (i = 0; i < 5; ++i) {
		if ( state[i].isWritten ) return false;
	}
	for (uidObj = 0; uidObj < 3; ++uidObj) {
		for ( i = 0; i < numStudents; ++i ) {
			if ( states[uidObj][i].isWritten ) return false;
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
		state[i].print( withDots );
		if ( ++i == 5 ) break;
		cout << "\t";
	}
	for ( uidObj = 0; uidObj < 3; ++uidObj ) {
		for ( uid = 0; uid < num[uidObj]; ++uid ) {
			cout << "\t";
			states[uidObj][uid].print( withDots );		
		}
	}
	cout << endl;
}

void print( Kind kind, char state ) {
	if ( state[kind].isWritten || state == 'F' ) flush( ! WITH_DOTS );
	state[kind]( state );
	if ( state == 'F' ) flush( WITH_DOTS );
}

void print( Kind kind, char state, int value1 ) {
	if ( state[kind].isWritten || state == 'F' ) flush( ! WITH_DOTS );
	state[kind]( state, value1 );
	if ( state == 'F' ) flush( WITH_DOTS );
}

void print( Kind kind, char state, int value1, int value2 ) {
	if ( state[kind].isWritten || state == 'F' ) flush( ! WITH_DOTS );
	state[kind]( state, value1, value2 );
	if ( state == 'F' ) flush( WITH_DOTS );
}

void print( Kind kind, unsigned int lid, char state ) {
	if ( states[INDEX(kind)][lid].isWritten || state == 'F' ) flush( ! WITH_DOTS );
	states[INDEX(kind)][lid]( state );
	if ( state == 'F' ) flush( WITH_DOTS );
}

void print( Kind kind, unsigned int lid, char state, int value1 ) {
	if ( states[INDEX(kind)][lid].isWritten || state == 'F' ) flush( ! WITH_DOTS );
	states[INDEX(kind)][lid]( state, value1 );
	if ( state == 'F' ) flush( WITH_DOTS );
}

void print( Kind kind, unsigned int lid, char state, int value1, int value2 ) {
	if ( states[INDEX(kind)][lid].isWritten || state == 'F' ) flush( ! WITH_DOTS );
	states[INDEX(kind)][lid]( state, value1, value2 );
	if ( state == 'F' ) flush( WITH_DOTS );
}

