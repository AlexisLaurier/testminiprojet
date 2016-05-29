#ifndef DIAGRAMME_H
#define DIAGRAMME_H

#include <iostream>
#include <string>
#include <vector>

#include "Mot.h"
#include "Menu.h"

using namespace std;
// Realise par Alexis LAURIER
enum Courbe { cercle, rectangle };
// Realise par Alexis LAURIER

class Diagramme {

	vector<Mot*> listeMot_;
	int nombreAffiche_;
	string police_;
	Courbe courbe_;
	double orientation_;

public:
	Diagramme();
	Diagramme(const Diagramme &diagramme);
	void creerListe();
	void choixMot();
	void afficher(MenuPrincipal &origine);
	void sauvegarde();
	void charger();
	void exporter();
	void setNombre();
	void setPolice();
	void setCourbe();
	void setOrientation();
	vector<Mot*> getListeMot() const { return listeMot_; }
	string getPolice() const { return police_; }
	Courbe getCourbe()const { return courbe_; }
	int getNombre() const { return nombreAffiche_; }
	double getOrientation() const { return orientation_; }

};










#endif