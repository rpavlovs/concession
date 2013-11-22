#ifndef __PRINTER_H__
#define __PRINTER_H__

#define INDEX(kind) ((kind) - 5)

_Monitor Printer {
		struct State {
			char state;
			int intOne, intTwo; 
			bool isWritten;
			State() : isWritten(false), intOne(-1), intTwo(-1) {};
			void print();
		};
		const unsigned int num[3];	// store numStudents numVendingMachines and numCouriers
		State state[5];			// states of Parent, WATCardOffice, NameServer, Truck and BottlingPlant
		State *states[3];		// states of Student, Vending, Courier
		void flush( bool withDots );
		bool isRowBufEmpty();
	public:
		enum Kind { Parent, WATCardOffice, NameServer, Truck, BottlingPlant, Student, Vending, Courier };
		Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers );
		void print( Kind kind, char state );
		void print( Kind kind, char state, int value1 );
		void print( Kind kind, char state, int value1, int value2 );
		void print( Kind kind, unsigned int lid, char state );
		void print( Kind kind, unsigned int lid, char state, int value1 );
		void print( Kind kind, unsigned int lid, char state, int value1, int value2 );
};

#endif
