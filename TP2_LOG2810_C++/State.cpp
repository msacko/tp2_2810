#include "State.h"

State::State(int id)
{
}


State::~State()
{
}

int State::getId()
{
	return id;
}

std::map<char, Branch*> State::getBranchs() {
	return branchs;
}
State* State::getPreviousState() {
	return previousState;
}

char State::getValue()
{
	return value;
}

void State::setBranchs(std::map<char, Branch*> branchs)
{
	this->branchs = branchs;
}

void State::setPrevious(State * state)
{
	this->previousState = state;
}

void State::setValue(char value)
{
	this->value = value;
}
