#include <iostream>
#include <iomanip>
#include <cstdlib>

#include "Menu.h"
using namespace std;

// Definition des methodes de la classe OptionMenu

OptionMenu::OptionMenu(const string &nom, const string &description)
	: nom_(nom), description_(description)
{
}


// Definition des methodes de la classe Menu

Menu::Menu(const string & titre) : titre_(titre)
{
	fin_ = false;
}


void Menu::ajouterOption(const string &nom, const string &description)
{
	listeOptions_.push_back(OptionMenu(nom, description));
}


void Menu::afficherMenu()
{
	cout << titre_ << endl;
	for (int i = 0; i<listeOptions_.size(); i++) {
		cout << "- " << setw(2) << i << " : " << listeOptions_[i].getDescription() << endl;
	}
}

int Menu::demanderChoix()
{
	int choix;
	cout << "Votre choix : ";
	cin >> choix;
	cout << endl;
	return choix;
}

void Menu::executer()
{
	bool fin = false;
	while (!fin) {
		system("cls");
		afficherMenu();
		int choix = demanderChoix();
		if (choix >= 0 && choix<listeOptions_.size())
			executerOption(listeOptions_[choix].getNom());
		else {
			cout << "Choix incorrect" << endl;
			system("pause");
		}
	}
}

void Menu::executerOption(const string &nom)
{
	if (nom == "quitter")
		quitter();
	else {
		cout << "Option inexistante" << endl;
		system("pause");
	}
}

void Menu::quitter()
{
	char reponse;
	cout << "Voulez-vous vraiment sortir de l'application (o/n) ?";
	cin >> reponse;
	if ((reponse == 'o') || (reponse == 'O')) fin_ = true;
}


// Définition de MenuPrincipal

MenuPrincipal::MenuPrincipal(const string & titre) : Menu(titre) {
	ajouterOption("chargerT", "Charger un Texte");
	ajouterOption("chargerT", "Charger un Texte");
	ajouterOption("chargerT", "Charger un Texte");
	ajouterOption("chargerT", "Charger un Texte");
	ajouterOption("chargerT", "Charger un Texte");
}

// Définition de MenuDiagramme
MenuDiagramme::MenuDiagramme(const string & titre) : Menu(titre) {

}

