#include "watcardOffice.h"

#include <iostream>

/* ******************
 * WATCard
 */

WATCardOffice::WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers ) : prt(&prt), bank(&bank),
				numCouriers(numCouriers) {

	for(unsigned int id = 0; id < numCouriers; id += 1) {
		courierList.push_back( new Courier( id, prt, bank, *this ) );
	}
	closed = false;
	prt.print( Printer::WATCardOffice, 'S' );
}

WATCardOffice::~WATCardOffice() {
	// delete couriers
	for (unsigned int id = 0; id < numCouriers; id += 1) {
		delete courierList[id];
	}

	// delete jobs
	while ( !jobsList.empty() ) {
		delete jobsList.front();
	}

	prt->print( Printer::WATCardOffice, 'F' );	
}


void WATCardOffice::main() {
	for (;;) {
		_Accept( ~WATCardOffice ) {
			closed = true;
//			std::cout << "wake up couriers" << std::endl;
			// wake up couriers so that they finish
			for (unsigned int id = 0; id < numCouriers; id += 1) {
				std::cout << "signal " << id << std::endl;
				workAvailable.signalBlock();
			}
			break;
		}
		or _Accept( requestWork ) {
		}
		or _Accept( create, transfer ) {
//			std::cout << "signalling" << std::endl;
			workAvailable.signalBlock();
		}
	}
}


WATCard::FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount ) {
//	std::cout << "create watcard sid: " << sid << " amount: " << amount << std::endl;
	WATCard *card = new WATCard();
	Job *job = new Job( sid, card, amount );
	jobsList.push( job );
	return job->result;
}

WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard *card ) {
//	std::cout << "transfer funds sid: " << sid << " amount: " << amount << std::endl;
	Job *job = new Job( sid, card, amount );
	jobsList.push( job );
	return job->result;
}

WATCardOffice::Job * WATCardOffice::requestWork() {
//	std::cout << "jobsList.size(): " << jobsList.size() << std::endl;
	if ( jobsList.empty() ) { 
//		std::cout << "waiting" << std::endl;
		workAvailable.wait();
	}

	if ( closed ) { 
//		std::cout << "end of day" << std::endl;
		return NULL;
	}
	WATCardOffice::Job * job = jobsList.front();
//	std::cout << "job ready job: " << job->studentId << std::endl;
			jobsList.pop();
	return job;
}



/* ******************
 * Courier
 */

WATCardOffice::Courier::Courier( unsigned int id, Printer &prt, Bank &bank, WATCardOffice &office ) 
				: id(id), prt(&prt), bank(&bank), office(&office) {
	prt.print( Printer::Courier, id, 'S' );
}

void WATCardOffice::Courier::main() {
	for (;;) {
//		std::cout << "requesting work" << std::endl;
		Job * job = office->requestWork();
		if ( job == NULL ) { 
			break; 
		}

		prt->print( Printer::Courier, id, 't', job->studentId, job->amount );

		bank->withdraw( job->studentId, job->amount );
		job->card->deposit( job->amount );
//		std::cout << "funds withdrawn, sid: " << job->studentId << std::endl;

		// card is lost
		if ( randGen(1,6) == 4 ) {
			job->result.exception( new Lost );
			prt->print( Printer::Courier, id, 'T', job->studentId, job->amount );
			delete job->card;
			delete job;
		}
		else {
//			std::cout << "delivering" << std::endl;
			job->result.delivery( job->card );
			prt->print( Printer::Courier, id, 'T', job->studentId, job->amount );

//			std::cout << "deleting" << std::endl;
			delete job;			
		}

	}
	prt->print( Printer::Courier, id, 'F' );
}
