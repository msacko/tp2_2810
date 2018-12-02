#pragma once
#include "Branch.h"
#include <map>

class State
{
public:
	State(int id);
	~State();

	int getId();
	std::map<char, Branch*> getBranchs();
	State* getPreviousState();
	char getValue();

	void setBranchs(std::map<char, Branch*> branchs);
	void setPrevious(State* state);
	void setValue(char value);


private :
	int id;
	char value;
	std::map<char, Branch*> branchs;
	State* previousState;
};

