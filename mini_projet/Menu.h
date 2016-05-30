#ifndef __MENU__
#define __MENU__

#include <string>
#include <vector>

#include "Diagramme.h"
#include "Mot.h"

class Menu;
class MenuPrincipal;
class MenuDiagramme;


class OptionMenu
{
	std::string nom_;
	std::string description_;
public:
	OptionMenu(const std::string &nom, const std::string &description);
	std::string getNom() const { return nom_; }
	std::string getDescription() const { return description_; }
};


class Menu
{
	Diagramme* diagramme_;
	std::string titre_;
	std::vector<OptionMenu> listeOptions_;
	bool fin_;
	

public:
	Menu(const std::string &titre);
	Menu(const std::string &titre, const Diagramme *diagramme);
	Menu(const std::string &titre, const Menu *copie);
	~Menu();
 	Diagramme getDiagramme()  const { return *diagramme_; }
	std::string getTitre() const { return titre_; }
	std::vector<OptionMenu> getListeOptions() const { return listeOptions_; }
	void ajouterOption(const std::string &nom, const std::string &description);
	void afficherMenu();
	int demanderChoix();
	void executer();
	virtual void executerOption(const std::string &nom);
	void quitter();
	Diagramme* getDiagramme() { return diagramme_; }
};


class MenuPrincipal : public Menu
{
public:
	MenuPrincipal();
	MenuPrincipal(const Diagramme &diagramme);
	MenuPrincipal(const MenuPrincipal *mp);
	void executerOption(const std::string &nom);
};

class MenuDiagramme : public Menu
{
public:
	MenuDiagramme(const Diagramme &diagramme);
	void executerOption(const std::string &nom);
};

#endif