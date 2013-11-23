#include "parent.h"

using namespace std;

Parent::Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay ) :
				printer(prt),
				bank(bank),
				numStudents(numStudents),
				parentalDelay(parentalDelay) {	

}

Parent::~Parent() {}

void Parent::main() {
	for (;;) {
		_Accept( ~Parent ) {
			break;
		}
		_Else {
			unsigned int amount = randGen(1,3);
			unsigned int studentId = randGen(numStudents-1);

			yield(parentalDelay);

			bank.deposit(studentId, amount);
		}
	}
}
