#include "Lexique.h"
#include <fstream>
#include <string>




Lexique::Lexique(std::string filename)
{
	ifstream fichier(filename);
	string ligne;

	while (!ws(fichier).eof())
	{
		while (getline(fichier, ligne))
		{
			if (!ligne.empty())
			{
				items.push_back(ligne);
			}
		}
	}
	fichier.close();
	nb_state = 0;
}


Lexique::~Lexique()
{
}

std::vector<std::string> Lexique::getItems()
{
	return items;
}

std::vector<State*> Lexique::getStates()
{
	return states;
}

void Lexique::setItem(std::vector<std::string> items)
{
	this->items = items;
}

void Lexique::setState(std::vector<State*> states)
{;
this->states = states;
}

void Lexique::addState(State * state)
{
	states.push_back(state);
}

void Lexique::setCurrentState(State * state)
{
	this->currentState = state;
}

State * Lexique::getCurrentState()
{
	if (currentState == nullptr) {
		return states[0];
	}
	return currentState;
}

bool containValue(int value, vector<int> list) {
	for (int i = 0; i < list.size(); i++)
		if (list[i] == value)
			return true;

	return false;
}

map<char, Branch*> Lexique::createBranchs(int index, vector<int> previous_branch_outputs)
{
	map<char, Branch*> branchs;
	for (int i = 0; i < items.size(); i++) {
		if (containValue(i, previous_branch_outputs)) {
			if (items[i].length() > index) {
				char key = items[i].at(index);

				if (branchs.find(key) == branchs.end()) {
					branchs[key] = new Branch();
				}

				branchs[key]->addOutput(i);
			}
		}
		
	}
	return branchs;
}

int Lexique::getBiggerItemCount()
{
	int max = 0;
	for (int i = 0; i < items.size(); i++) {
		if (items[i].length() > max) {
			max = items[i].length();
		}
	}
	return max;
}


void Lexique::buildAutomate()
{
	vector<State*> currents_states_ids;
	vector<State*> next_states_ids;

	currents_states_ids.push_back(new State(nb_state++));

	int maxIndex = getBiggerItemCount();
	int current_position = 0;


	while (current_position < maxIndex) {

		for (State*  current_state  : currents_states_ids) {

			vector<int> previous_branchs_output;
			if (current_state->getPreviousState() == nullptr) {
				for (int j = 0; j < items.size(); j++)
					previous_branchs_output.push_back(j);
			}
			else
				previous_branchs_output = current_state->getPreviousState()->getBranchs()[current_state->getValue()]->getOutput();

			map<char, Branch*> branchs = createBranchs(current_position, previous_branchs_output);
			for (map<char, Branch*>::iterator it = branchs.begin(); it != branchs.end(); ++it)
			{
				State* next_state = new State(nb_state++);

				next_state->setPrevious(current_state);
				next_state->setValue(it->first);

				it->second->setNextState(next_state);

				next_states_ids.push_back(next_state);

			}
			
			current_state->setBranchs(branchs);
			states.push_back(current_state);

		}

		currents_states_ids = next_states_ids;
		next_states_ids.clear();

		current_position++;
	}

}






