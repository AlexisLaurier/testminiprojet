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
	int nombreOccurenceChoisi_;

public:
	Diagramme();
	Diagramme(const Diagramme &diagramme);
	void ajouterMot(Mot * mot);
	void choixMot();
	void afficher(MenuPrincipal &origine);
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
	Courbe getCourbe()const { return courbe_; }
	int getNombre() const { return nombreAffiche_; }
	double getOrientation() const { return orientation_; }
	int getnombreOccurenceChoisi() const { return nombreOccurenceChoisi_; }
	void setnombreOccurenceChoisi(int : n) { nombreOccurenceChoisi_ = n; }

};










#endif