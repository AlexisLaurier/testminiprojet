#include <iostream>
#include <iomanip>
#include <cstdlib>

#include "Menu.h"
#include "Diagramme.h"

using namespace std;

// Definition des methodes de la classe OptionMenu

OptionMenu::OptionMenu(const string &nom, const string &description)
	: nom_(nom), description_(description)
{
}


// Definition des methodes de la classe Menu

Menu::Menu(const string &titre) : titre_(titre)
{
	listeOptions_.clear();
	diagramme_ = new Diagramme;
	fin_ = false;
}

Menu::Menu(const string &titre, const Diagramme *diagramme) : titre_(titre) {
	listeOptions_.clear();
	diagramme_ = new Diagramme(*diagramme);
	fin_ = false;
}

Menu::Menu(const string &titre, const Menu *copie) : titre_(titre)
{
	titre_ = copie->getTitre();
	listeOptions_.clear();
	for (int count = 0;count < copie->getListeOptions().size();count++)
		listeOptions_.push_back(copie->getListeOptions().at(count));	diagramme_ = new Diagramme(copie->getDiagramme());
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
		cout << "- " << setw(2) << i+1 << " : " << listeOptions_[i].getDescription() << endl;
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
	while (!fin_) {
		system("cls");
		afficherMenu();
		int choix = demanderChoix();
		if (choix >= 1 && choix<=listeOptions_.size())
			executerOption(listeOptions_[choix-1].getNom());
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
		if ((reponse == 'o') || (reponse == 'O')) {
			fin_ = true;
			if(diagramme_->getMenu())
				delete diagramme_->getMenu();
		}
	

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

MenuPrincipal::MenuPrincipal(const Diagramme *diagramme) : Menu("Createur de nuage de mot",diagramme){
	ajouterOption("chargerT", "Charger un texte");
	ajouterOption("choisirM", "Choisir les mots a garder");
	ajouterOption("genDiag", "Generer le nuage de mot");
	ajouterOption("sauvegarde", "Sauvegarde");
	ajouterOption("chargerSauv", "Charger une sauvegarde precedente");
	ajouterOption("quitter", "Quitter le programme");
}


MenuPrincipal::MenuPrincipal(const MenuPrincipal *mp) : Menu("Createur de nuage de mot",mp) {
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
	else if (nom == "sauvegarde")
		getDiagramme()->sauvegarde();
	else if (nom == "chargerSauv")
		getDiagramme()->charger();
	else
		Menu::executerOption(nom);

}


// Définition de MenuDiagramme

MenuDiagramme::MenuDiagramme(const Diagramme &diagramme) : Menu("Gestion du nuage de mot", &diagramme) {
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
		getDiagramme()->choixPolice();
	else if (nom == "chgOrientation")
		getDiagramme()->choixOrientation();
	else if (nom == "chgCourbe")
		getDiagramme()->choixCourbe();
	else if (nom == "chgNb")
		getDiagramme()->choixNombre();
	else if (nom == "export")
		getDiagramme()->exporter();
	else if (nom == "retour") {
		MenuPrincipal menuPrincipal(getDiagramme());
		menuPrincipal.executer();
	}
	else
		Menu::executerOption(nom);

}

