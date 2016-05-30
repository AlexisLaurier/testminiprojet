#ifndef TEST2
#define TEST2

#include <iostream>
#include <string>
#include <vector>

#include "Mot.h"
#include "Menu.h"

class Diagramme;
class Menu;

// Realise par Alexis LAURIER
enum Courbe { cercle, rectangle };
// Realise par Alexis LAURIER



class Diagramme {

	std::vector<Mot*> listeMot_;
	int nombreAffiche_;
	std::string police_;
	Courbe courbe_;
	double orientation_;

public:
	Diagramme();
	Diagramme(const Diagramme &diagramme);
	void creerListe();
	void choixMot();
	void afficher(Menu &origine);
	void sauvegarde();
	void charger();
	void exporter();
	void setNombre();
	void setPolice();
	void setCourbe();
	void setOrientation();
	std::vector<Mot*> getListeMot() const { return listeMot_; }
	std::string getPolice() const { return police_; }
	Courbe getCourbe()const { return courbe_; }
	int getNombre() const { return nombreAffiche_; }
	double getOrientation() const { return orientation_; }

};



#endif