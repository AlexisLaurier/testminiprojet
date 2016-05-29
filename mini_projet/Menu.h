#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>

#include "Diagramme.h"
#include "Mot.h"

using namespace std;


class OptionMenu
{
	string nom_;
	string description_;
public:
	OptionMenu(const string &nom, const string &description);
	string getNom() const { return nom_; }
	string getDescription() const { return description_; }
};


class Menu
{
	string titre_;
	vector<OptionMenu> listeOptions_;
	bool fin_;
	Diagramme *diagramme_;

public:
	Menu(const string &titre);
	Menu(const Menu *copie);
	~Menu();
	Diagramme getDiagramme()  const { return *diagramme_; }
	string getTitre() const { return titre_; }
	vector<OptionMenu> getListeOptions() const { return listeOptions_; }
	void ajouterOption(const string &nom, const string &description);
	void afficherMenu();
	int demanderChoix();
	void executer();
	virtual void executerOption(const string &nom);
	void quitter();
	Diagramme *getDiagramme() { return diagramme_; }
};


class MenuPrincipal : public Menu
{
public:
	MenuPrincipal();
	MenuPrincipal(const MenuPrincipal *mp);
	void executerOption(const string &nom);
};

class MenuDiagramme : public Menu
{
	MenuPrincipal *origine_;
public:
	MenuDiagramme(MenuPrincipal *origine);
	void executerOption(const string &nom);
};

#endif