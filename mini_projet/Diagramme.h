#ifndef __DIAGRAMME__
#define __DIAGRAMME__

#include <iostream>
#include <string>
#include <vector>

#include "CImg.h"
#include "Mot.h"
#include "Menu.h"

#define NOMBRE_DE_COURBE 2


class Diagramme;
class Menu;
class MenuPrincipal;
class MenuDiagramme;

// Realise par Alexis LAURIER
enum Courbe { cercle, rectangle };
// Realise par Alexis LAURIER

typedef struct Point{
	int x;
	int y;
	int posCourbe;
};


class Diagramme {

	std::vector<Mot*> listeMot_;
	int nombreAffiche_;
	std::string police_;
	Courbe courbe_;
	double orientation_;
	MenuDiagramme *menu_;
	MenuPrincipal *origine_;
	int nombreOccurenceChoisi_;
	cimg_library::CImg<unsigned char> scene_;

public:
	Diagramme();
	Diagramme(const Diagramme &diagramme);
	void creerListe();
	void ajouterMot(Mot * mot);
	void choixMot();
	void afficher(MenuPrincipal &origine, bool reload = false);
	void sauvegarde();
	void charger();
	void exporter();
	void setnombreAffiche(int n) { nombreAffiche_ = n; }
	int getnombreAffiche() const { return nombreAffiche_; }
	void setPolice(std::string police) { police_ = police; }
	std::string getPolice() { return police_; }
	void setCourbe(Courbe courbe) { courbe_ = courbe; };
	void choixOrientation();
	void choixNombre();
	void choixPolice();
	void choixCourbe();
	void setOrientation(double orientation) { orientation_ = orientation; }
	void setOrigine(MenuPrincipal* origine) { origine_ = origine; }
	std::vector<Mot*> getListeMot() const { return listeMot_; }
	std::string getPolice() const { return police_; }
	Courbe getCourbe() const { return courbe_; }
	int getNombre() const { return nombreAffiche_; }
	double getOrientation() const { return orientation_; }
	int getnombreOccurenceChoisi() const { return nombreOccurenceChoisi_; }
	void setnombreOccurenceChoisi(int  n) { nombreOccurenceChoisi_ = n; }
	MenuDiagramme* getMenu() const { return menu_; }
	MenuPrincipal* getOrigine() const { return origine_; }
	Point prochainPoint(Courbe courbe, Point pointActuelle);

};


std::string nomCourbe(int idCourbe);


#endif