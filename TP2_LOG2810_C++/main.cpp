#include "Lexique.h"


int main() {

	Lexique lexique1("lexique1.txt");

	lexique1.buildAutomate();
	char choix;
	
	string chaine = "";
	State* currentState = lexique1.getCurrentState();
	cout << "Saisissez votre mot" << endl;
	do
	{
		cin >> choix;
		chaine += choix;
		if (currentState->getBranchs()[choix] != nullptr) {

			cout << "Resultat pour : " << chaine.c_str() << endl;
			for (int i = 0; i < currentState->getBranchs()[choix]->getOutput().size(); i++)
			{
				std::string result = lexique1.getItems()[currentState->getBranchs()[choix]->getOutput()[i]];
				cout << result.c_str() << "\n";
			}
			currentState = currentState->getBranchs()[choix]->getNextState();
		}

		
		cout << endl << "Dernier mot saisie : " << chaine.c_str();

		cout << endl;
	} while (choix != '0');

	return 0;
}