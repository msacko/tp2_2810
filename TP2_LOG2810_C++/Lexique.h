#pragma once
#include "state.h"
#include <iostream>

using namespace std;

class Lexique
{
public:
	Lexique(string filename);
	~Lexique();

	vector<std::string>  getItems();
	vector<State*> getStates();

	void setItem(std::vector<std::string> items);
	void setState(std::vector<State*> states);

	void addState(State* state);
	void setCurrentState(State* state);
	State* getCurrentState();
	

	map<char, Branch*> createBranchs(int index, vector<int> previous_branch_outputs);

	void buildAutomate();

	int getBiggerItemCount();
	
private:
	vector<string> items;
	vector<State*> states;
	int nb_state;

	State* currentState;
};

