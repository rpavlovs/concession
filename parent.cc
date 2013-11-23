#include "parent.h"

Parent::Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay ) :
				prt(&prt),
				bank(&bank),
				numStudents(numStudents),
				parentalDelay(parentalDelay) {	
}

Parent::~Parent() {
	prt->print( Printer::Parent, 'D' );
}

void Parent::main() {
	prt->print( Printer::Parent, 'S' );

	for (;;) {
		_Accept( ~Parent ) {
			break;
		}
		_Else {
			int amount = randGen(1,3);
			unsigned int studentId = randGen( numStudents - 1 );

			yield( parentalDelay );

			prt->print( Printer::Parent, 'D', studentId, amount);
			bank->deposit( studentId, amount );
		}
	}
}
