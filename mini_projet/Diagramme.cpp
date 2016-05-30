#include <iostream>
#include <string>
#include <vector>

#include "Menu.h"
#include "Diagramme.h"


using namespace std;


Diagramme::Diagramme() {
	listeMot_.clear();
	nombreAffiche_ = 50;  //50 mots par défaut
	police_; // Police par défaut à définir
	courbe_ = cercle; 
	orientation_ = 45.0; // Inclinaison par défaut de +/- 45°
	menu_ = new MenuDiagramme(*this);
}

Diagramme::Diagramme(const Diagramme & diagramme) {
	listeMot_.clear();
	for (int count = 0; count < diagramme.getListeMot().size();count++) {
		listeMot_.push_back(diagramme.getListeMot().at(count));
	}
	nombreAffiche_ = diagramme.getNombre();
	police_ = diagramme.getPolice();
	courbe_ = diagramme.getCourbe();
	orientation_ = diagramme.getOrientation();
	menu_ = diagramme.getMenu();
}


void Diagramme::creerListe() {

}

void Diagramme::choixMot() {

}

void Diagramme::afficher() {
	// Création et affichage du nuage à ajouter

	MenuDiagramme sousMenu(*this);
	sousMenu.executer();
}

void Diagramme::sauvegarde() {

}

void Diagramme::charger() {

}

void Diagramme::exporter() {

}

void Diagramme::setNombre() {

		system("cls");
		cout << "Actuellement, le nuage affiche " << getNombre() << " mots, combien souhaitez vous en afficher ?" << endl;
		cin >>  nombreAffiche_;

}

void Diagramme::setPolice() {

}

void Diagramme::setCourbe() {

}

void Diagramme::setOrientation() {

}