#ifndef __WATCARD_OFFICE_H__
#define __WATCARD_OFFICE_H__

#include "MPRNG.h"
#include "watcard.h"
#include "printer.h"
#include "bank.h"

#include <vector>
#include <queue>

extern MPRNG randGen;

_Task WATCardOffice {
    struct Job {                            // marshalled arguments and return future
        unsigned int studentId;             //
        unsigned int amount;                // 
        WATCard * card;                     // 
        WATCard::FWATCard result;                    // return future
        Job( unsigned int studentId, WATCard * card, unsigned int amount ) 
            : studentId(studentId), amount(amount), card(card) {}
    };
    _Task Courier {                         // communicates with bank
          unsigned int id;
          Printer * prt;
          Bank * bank;
          WATCardOffice * office;
          void main();
        public:
          Courier( unsigned int id, Printer &prt, Bank &bank, WATCardOffice &office );
    };

    Printer * prt;
    Bank * bank;
    unsigned int numCouriers;
    std::vector<Courier*> courierList;
    std::queue<Job*> jobsList;
    uCondition workAvailable;
    bool closed;

    void main();
  public:
    ~WATCardOffice();
    _Event Lost {};                        // uC++ exception type, like "struct"
    WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers );
    WATCard::FWATCard create( unsigned int sid, unsigned int amount );
    WATCard::FWATCard transfer( unsigned int sid, unsigned int amount, WATCard *card );
    Job *requestWork();
};

#endif
