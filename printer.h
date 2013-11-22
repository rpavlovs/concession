#ifndef __PRINTER_H__
#define __PRINTER_H__

#include "uC++.h"

#define INDEX(kind) (((int)kind) - 5)

_Monitor Printer {
		struct State {
			char state;
			int intOne, intTwo; 
			bool isWritten;
			State() : intOne(-1), intTwo(-1), isWritten(false) {};
			void print( bool withDots );
			void set( char s );
			void set( char s, int value1 );
			void set( char s, int value1, int value2 );
		};
		unsigned int num[3];	// store numStudents numVendingMachines and numCouriers
		State nonlidStates[5];			// states of Parent, WATCardOffice, NameServer, Truck and BottlingPlant
		State *lidStates[3];		// states of Student, Vending, Courier
		void flush( bool withDots );
		bool isRowBufEmpty();
	public:
		enum Kind { Parent, WATCardOffice, NameServer, Truck, BottlingPlant, Student, Vending, Courier };
		Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers );
		~Printer();
		void print( Kind kind, char state );
		void print( Kind kind, char state, int value1 );
		void print( Kind kind, char state, int value1, int value2 );
		void print( Kind kind, unsigned int lid, char state );
		void print( Kind kind, unsigned int lid, char state, int value1 );
		void print( Kind kind, unsigned int lid, char state, int value1, int value2 );
};

#endif
