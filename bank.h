#ifndef __BANK_H__
#define __BANK_H__

#include <vector>

_Monitor Bank {

	unsigned int numStudents;
	std::vector<unsigned int> balances;
	std::vector<uCondition*> conditions; 

  public:
    Bank( unsigned int numStudents );
	~Bank();
    void deposit( unsigned int id, unsigned int amount );
    void withdraw( unsigned int id, unsigned int amount );
};

#endif
