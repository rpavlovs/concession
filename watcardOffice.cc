#include "watcardOffice.h"

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
			// wake up couriers so that they finish
			for (unsigned int id = 0; id < numCouriers; id += 1) {
				workAvailable.signal();
			}
			break;
		}
		or _Accept( requestWork ) {

		}
		or _Accept( create, transfer ) {
			workAvailable.signal();
		}
	}
}


WATCard::FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount ) {
	WATCard *card = new WATCard();
	Job *job = new Job( sid, card, amount );
	jobsList.push( job );
	return job->result;
}

WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard *card ) {
	Job *job = new Job( sid, card, amount );
	jobsList.push( job );
	return job->result;
}

WATCardOffice::Job * WATCardOffice::requestWork() {
	if ( jobsList.empty() ) { workAvailable.wait(); }
	if ( closed ) { 
		return NULL;
	}
	return jobsList.front();
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
		Job * job = office->requestWork();
		if ( job == NULL ) { 
			break; 
		}

		prt->print( Printer::Courier, id, 't', job->studentId, job->amount );

		bank->withdraw( job->studentId, job->amount );

		// card is lost
		if ( randGen(1,6) == 4 ) {
			job->result.exception( new Lost );
			delete job->card;
			return;
		}

		job->result.delivery( job->card );
		prt->print( Printer::Courier, id, 'T', job->studentId, job->amount );

		delete job;
	}
	prt->print( Printer::Courier, id, 'F' );
}
