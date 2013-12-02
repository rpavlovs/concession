#include "watcardOffice.h"

/* ******************
 * WATCard
 */

WATCardOffice::WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers ) : prt(&prt), bank(&bank),
				numCouriers(numCouriers) {
	prt.print( Printer::WATCardOffice, 'S' );

	for(unsigned int id = 0; id < numCouriers; id += 1) {
		courierList.push_back( new Courier( prt, bank, *this ) );
	}

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

	return jobsList.front();
}



/* ******************
 * Courier
 */

WATCardOffice::Courier::Courier( Printer &prt, Bank &bank, WATCardOffice &office ) : prt(&prt), bank(&bank),
					office(&office) {

}

void WATCardOffice::Courier::main() {
	for (;;) {
		Job * job = office->requestWork();

		bank->withdraw( job->studentId, job->amount );

		// card is lost
		if ( randGen(1,6) == 4 ) {
			job->result.exception( new Lost );
			delete job->card;
			return;
		}

		job->result.delivery( job->card );

		delete job;
	}
}
