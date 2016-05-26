#ifndef __DIAGRAMME__
#define __DIAGRAMME__
#include <iostream>
#include <string>
#include <vector>

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
	void creerListe();
	void afficher();
	void sauvegarde();
	void export();
	void setNombre();
	void setPolice();
	void setCourbe();
	void setOrientation();
	string getPolice() { return police_; };
	Courbe getCourbe() { return courbe_; };
	int getNombre() { return nombreAffiche_; };
	double getOrientation() { return orientation_; };

}



};










#endif