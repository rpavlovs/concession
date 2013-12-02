#include "bank.h"

#include <iostream>

using namespace std;

Bank::Bank( unsigned int numStudents ) : numStudents(numStudents) {

	for(unsigned int id = 0; id < numStudents; id += 1) {
		balances.push_back(0);
		conditions.push_back( new uCondition() );
	}
}

Bank::~Bank() {
	for(unsigned int id = 0; id < numStudents; id += 1) {
		delete conditions[id];
	}
}

void Bank::deposit( unsigned int id, unsigned int amount ) {
	if ( id > balances.size() ) { return; }

	// deposit amount
	balances[id] += amount;

	// wake up courier
	if ( !conditions[id]->empty() && (unsigned int) conditions[id]->front() <= balances[id] ) {
		// if the balance is gte the amount waiting for
		conditions[id]->signal();
	}
}

void Bank::withdraw( unsigned int id, unsigned int amount ) {
	if ( id > balances.size() ) { return; }

	if ( amount > balances[id] ) {
//		std::cout << "waiting for funds" << std::endl;
		// wait for enough money to be deposited
		conditions[id]->wait( amount );
	}

//	std::cout << "withdrawing" << std::endl;
	balances[id] -= amount;
}
