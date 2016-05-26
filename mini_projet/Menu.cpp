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
	diagramme_ = new Diagramme;
	fin_ = false;
}

Menu::~Menu() {
	delete diagramme_;
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

MenuPrincipal::MenuPrincipal() : Menu("Createur de nuage de mot") {
	ajouterOption("chargerT", "Charger un texte");
	ajouterOption("choisirM", "Choisir les mots a garder");
	ajouterOption("genDiag", "Generer le nuage de mot");
	ajouterOption("sauvegarde", "Sauvegarde");
	ajouterOption("chargerSauv", "Charger une sauvegarde precedente");
	ajouterOption("quitter", "Quitter le programme");
}

void MenuPrincipal::executerOption(const string &nom) {
	if (nom == "chargerT")
		getDiagramme()->creerListe();
	else if (nom == "choisirM")
		getDiagramme()->choixMot();
	else if (nom == "genDiag")
		getDiagramme()->afficher();
	else if (nom == "sauvagrde")
		getDiagramme()->sauvegarde();
	else if (nom == "chargerSauv")
		getDiagramme()->charger();
	else
		Menu::executerOption(nom);

}


// Définition de MenuDiagramme
MenuDiagramme::MenuDiagramme() : Menu("Gestion du nuage de mot") {
	ajouterOption("reload", "Deplacer les mots (aleatoirement)");
	ajouterOption("chgPolice", "Changer la police des mots");
	ajouterOption("chgOrientation", "Changer l'orientation des mots");
	ajouterOption("chgCourbe", "Changer la courbe de base");
	ajouterOption("chgNb", "Changer le nombre de mot affiche");
	ajouterOption("export", "Sauvegarder l'image du nuage");
	ajouterOption("retour", "Retour au menu principal");
}

void MenuDiagramme::executerOption(const string &nom) {
	if (nom == "reload")
		getDiagramme()->afficher();
	else if (nom == "chgPolice")
		getDiagramme()->setPolice();
	else if (nom == "chgOrientation")
		getDiagramme()->setOrientation();
	else if (nom == "chgCourbe")
		getDiagramme()->setCourbe();
	else if (nom == "chgNb")
		getDiagramme()->setNombre();
	else if (nom == "export")
		getDiagramme()->exporter();
	else if (nom == "retour")
		menuPrincipal_.executer();
	else
		Menu::executerOption(nom);

}

