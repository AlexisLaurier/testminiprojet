#ifndef TEST2
#define TEST2

#include <iostream>
#include <string>
#include <vector>

#include "Mot.h"
#include "Menu.h"

class Diagramme;
class Menu;
class MenuPrincipal;
class MenuDiagramme;

// Realise par Alexis LAURIER
enum Courbe { cercle, rectangle };
// Realise par Alexis LAURIER



class Diagramme {

	std::vector<Mot*> listeMot_;
	int nombreAffiche_;
	std::string police_;
	Courbe courbe_;
	double orientation_;
	MenuDiagramme *menu_;
	int nombreOccurenceChoisi_;

public:
	Diagramme();
	Diagramme(const Diagramme &diagramme);
	void ajouterMot(Mot * mot);
	void choixMot();
	void afficher();
	void sauvegarde();
	Diagramme charger(string chemin)
	void exporter();
	void setNombre();
	void setnombreAffiche(int n) { nombreAffiche_ = n; }
	int getnombreAffiche() { return nombreAffiche_; }
	void setPolice(string police) {police_ = police;}
	string getPolice(){return police_}
	void setCourbe(string courbe) { courbe_ = courbe; };
	void choixOrientation();
	void setOrientation(double orientation) { orientation_ = orientation; }
	vector<Mot*> getListeMot() const { return listeMot_; }
	string getPolice() const { return police_; }
	void setPolice();
	void setCourbe();
	void setOrientation();
	std::vector<Mot*> getListeMot() const { return listeMot_; }
	std::string getPolice() const { return police_; }
	Courbe getCourbe()const { return courbe_; }
	int getNombre() const { return nombreAffiche_; }
	double getOrientation() const { return orientation_; }
	int getnombreOccurenceChoisi() const { return nombreOccurenceChoisi_; }
	void setnombreOccurenceChoisi(int : n) { nombreOccurenceChoisi_ = n; }
	MenuDiagramme* getMenu() const { return menu_; }

};



#endif