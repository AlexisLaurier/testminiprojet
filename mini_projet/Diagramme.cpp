#include <iostream>
#include <string>
#include <vector>

#include "Diagramme.h"


using namespace std;


Diagramme::Diagramme() {
	listeMot_.clear();
	nombreAffiche_ = 50;  //50 mots par d�faut
	police_; // Police par d�faut � d�finir
	courbe_ = cercle; 
	orientation_ = 45.0; // Inclinaison par d�faut de +/- 45�
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
}


void Diagramme::creerListe() {

}

void Diagramme::choixMot() {

}

void Diagramme::afficher(MenuPrincipal &origine) {
	// Cr�ation et affichage du nuage � ajouter

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