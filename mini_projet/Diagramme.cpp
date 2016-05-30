#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>

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

void Diagramme::ajouterMot(Mot * mot) {

	listeMot_.push_back(mot);

}

void Diagramme::choixMot() {
	int page=0;
	vector<Mot*>::iterator it; 
	cout << left << setw(40) << "Mot : " << setw(19) << "Nombre apparition" << setw(14) << "L'afficher ?" << endl;
	for (it = listeMot_.begin()+(15*page); (it != listeMot_.end()) && (it != (listeMot_.begin() + 15 * page + 15)); it++)
	{
		string affiche;
		if ((*it)->getChoisi()) { affiche = "oui"; }
		else { affiche = "non"; };
		cout << left << setw(40) << (*it)->getText() << setw(8) << (*it)->getOccurence() << setw(8) << affiche << endl;
	}
	cout << "Affichage de la page " << page + 1 << endl;

}

void Diagramme::afficher() {
	// Création et affichage du nuage à ajouter
	if(menu_)
		menu_->executer();
}

void Diagramme::sauvegarde() {
	string chemin, nom;
	cout << "Dans quel dossier dois-je effectuer la sauvegarde ?" << endl;
	cin >> chemin;
	cout << "Quel nom de fichier doit avoir la sauvegarde ?" << endl;
	cin >> nom;
	chemin = chemin + nom;
	ofstream fich(chemin.c_str());
	if (!fich.is_open()) cout << "Impossible d'enregistrer ici, verifier le chemin du fichier" << endl;
	else
	{
		fich << "<listemot>" << endl;
		vector<Mot*>::iterator it; // Déclaration de l'itérateur
		for (it = listeMot_.begin(); it != listeMot_.end();it++)
			{
				fich << (*it)->getText() << endl;
				fich << (*it)->getOccurence() << endl;
				fich << (*it)->getChoisi() << endl;
			}
		fich << "</listemot>" << endl;
		fich << "<settings>" << endl;
		fich << nombreOccurenceChoisi_ << endl;
		fich << nombreAffiche_ << endl;
		fich << police_ << endl;
		fich << courbe_ << endl;
		fich << orientation_ << endl;

	}

}

Diagramme Diagramme::charger() {

	Diagramme diag;
	char reponse;
	string chemin;
	cout << "Attention, les donnees non enregistrées seront effacées" << endl;
	cout << "Souhaitez-vous poursuivre ? (o/n)" << endl;
	cin >> reponse;
	if ((reponse == 'o') || (reponse == 'O')) {
		exit;
	}
	cout << "Merci de saisir le chemin du fichier à ouvrir" << endl;
	cin >> chemin;
	ifstream fich(chemin.c_str());
	if (!fich.is_open()) cout << "Erreur d'ouverture, verifier le chemin du fichier" << endl;
	else
	{
		string ligne;
		do { getline(fich, ligne);
		}
		while (ligne != "<listemot>");

		do { 		
			getline(fich, ligne);
			Mot mot(ligne);
			getline(fich, ligne);
			mot.setOccurence(stoi(ligne));
			getline(fich, ligne);
			mot.setChoisi(ligne == "1");
			diag.ajouterMot(&mot);

		}		
		while (ligne != "</listemot>");

		do {
				getline(fich, ligne);

		} 
		while (ligne != "<settings>");
		getline(fich, ligne);
		diag.setnombreOccurenceChoisi(stoi(ligne));
		getline(fich, ligne);
		diag.setnombreAffiche(stoi(ligne));
		getline(fich, ligne);
		diag.setPolice(ligne);
		getline(fich, ligne);
		diag.setCourbe(static_cast<Courbe>(stoi(ligne)));
		getline(fich, ligne);
		diag.setOrientation(stoi(ligne));
		getline(fich, ligne);
		if (ligne!="</settings") {
			cerr << "sauvegarde endommagée" << endl;
		}
		return diag;

	}

}

void Diagramme::exporter() {

}


void Diagramme::choixOrientation() {

}

void Diagramme::choixNombre() {
		system("cls");
		cout << "Actuellement, le nuage affiche " << getNombre() << " mots, combien souhaitez vous en afficher ?" << endl;
	cin >> nombreAffiche_;
}

void Diagramme::choixPolice() {

}

void Diagramme::choixCourbe() {

}