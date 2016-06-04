#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <fstream>
#include <ctype.h>
#include <sstream>
#include <algorithm>

#include "Menu.h"
#include "Diagramme.h"
#include "filedialog.h"

#pragma warning(disable:4996)

using namespace std;

bool comparerMot(const Mot *elem1, const Mot *elem2)
{
	return elem1->getOccurence() > elem2->getOccurence();
}

Diagramme::Diagramme() {
	listeMot_.clear();
	nombreAffiche_ = 50;  //50 mots par défaut
	police_ = "testPolice"; // Police par défaut à définir
	courbe_ = cercle; 
	orientation_ = 45.0; // Inclinaison par défaut de +/- 45°
	menu_ = new MenuDiagramme(*this);
	origine_ = new MenuPrincipal(*this);
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
	origine_ = diagramme.getOrigine();
}


/*

void Tokenize(const string& str,
	vector<string>& tokens,
	const string& delimiters = " ;,.")
{
	// Skip delimiters at beginning.
	string::size_type lastPos = str.find_first_not_of(delimiters, 0);
	// Find first "non-delimiter".
	string::size_type pos = str.find_first_of(delimiters, lastPos);

	while (string::npos != pos || string::npos != lastPos)
	{
		// Found a token, add it to the vector.
		(str.substr(lastPos, pos - lastPos);
		// Skip delimiters.  Note the "not_of"
		lastPos = str.find_first_not_of(delimiters, pos);
		// Find next "non-delimiter"
		pos = str.find_first_of(delimiters, lastPos);
	}
}

*/


void Diagramme::creerListe() 
{
	char reponse;
	cout << "Attention, les donnees non enregistrées seront effacées" << endl;
	cout << "Souhaitez-vous poursuivre ? (o/n)" << endl;
	cin >> reponse;
	if ((reponse == 'o') || (reponse == 'O'))

	{


	}

	string nomOpen = getOpenFileName("Nom du fichier à charger :", "Fichiers txt (*.txt )");

	if (nomOpen != "")
	{
		cout << "Nom du fichier chargé : " << nomOpen << endl;
		ifstream fich(nomOpen.c_str());
		if (!fich.is_open())
		{

			cout << "Erreur d'ouverture, verifier le chemin du fichier" << endl;
		}
		else
		{
			string line;

				while (getline(fich, line))
				{
					string str = line;
					const string& delimiters = " ;,.";
						// Skip delimiters at beginning.
						string::size_type lastPos = str.find_first_not_of(delimiters, 0);
					// Find first "non-delimiter".
					string::size_type pos = str.find_first_of(delimiters, lastPos);

					while (string::npos != pos || string::npos != lastPos)
					{
						// Found a token, add it to the vector list if word doesn't already exist.
						string motExtrait = str.substr(lastPos, pos - lastPos);
						vector<Mot*>::iterator it; // Déclaration de l'itérateur
						Mot *motAAjouter = new Mot;
						it = listeMot_.begin();
						int trouve = 0;
						while ((it != listeMot_.end()) && trouve == 0)
						{
							if (*(*it)->getText() == motExtrait)
							{
								trouve = 1;
								(*it)->apparu();
							}
							it++;
						}
						if (trouve == 0)
						{
							motAAjouter->setText(motExtrait);
							listeMot_.push_back(motAAjouter);
						}
						// Skip delimiters.  Note the "not_of"
						lastPos = str.find_first_not_of(delimiters, pos);
						// Find next "non-delimiter"
						pos = str.find_first_of(delimiters, lastPos);
					}

				}

				sort(listeMot_.begin(), listeMot_.end(), comparerMot);
		}
	}
}

void Diagramme::ajouterMot(Mot * mot) {

	listeMot_.push_back(mot);

}

void Diagramme::choixMot() {
	int page = 0; int i = 0;
	vector<Mot*>::iterator it; 
	cout << left << setw(14) << "N°ligne" << setw(25) << "Mot : " << setw(22) << "Nombre d'apparition" << setw(14) << "L'afficher ?" << endl;
	char tap;
	char *choix=&tap;
	do {
		for (it = listeMot_.begin() + (15 * page); (it != listeMot_.end()) ; it++)
		{
			string affiche;
			if ((*it)->getChoisi()) { affiche = "oui"; }
			else { affiche = "non"; };
			cout << left << setw(14) << i << setw(25) << *(*it)->getText() << setw(22) << (*it)->getOccurence() << setw(14) << affiche << endl;
			i += 1;
		}
		i = 0;
		cout << "Affichage de la page " << page + 1 << endl;
		cout << "Changer statut mot : numero ligne ; Changer numero page : p+, p-, px ;retourner menu principal : exit" << endl;
		cin >> tap;
		if (isdigit(*choix))
		{
			int j = tap;
			(listeMot_[j])->changeChoisi();
			
		}
		else {
			if(choix[0] == 'p')
			{ 
				switch (*choix)
				{
				case 'p+':
				{page = page + 1; }
				case 'p-':
				{
					if (page >= 1)
					{
						page = page - 1;
					}
					else
						cout << "vous etes deja a la premiere page !" << endl;
				
				}
				default :
				{
					char* ch = { 0 };
					strcpy_s(ch, strlen(choix),choix + 1);
					if(isdigit(*ch))
					{
						page = *ch;
					}
					else {
						cout << "choix incorrect" << endl;
						system("pause");
					}

				}

			}
			
			}
			
			

		}
		
		system("cls");
	} while (tap != 'exit');

}

void Diagramme::afficher(MenuPrincipal &origine, bool reload) {
	// Création et affichage du nuage à ajouter


	if (!reload) {
		origine_ = &origine;
		menu_->getDiagramme()->setOrigine(&origine);
		menu_->executer();

		
	}
	
}

void Diagramme::sauvegarde() {
	cout << "Merci de choisir dans quel fichier effectuer la sauvegarde" << endl;
	string nomSave = getSaveFileName("Nom du fichier à sauvegarder :", "Fichiers genmots (*.genmots )");
	if (nomSave != "")
	{
		cout << "Nom du fichier sauvegardé : " << nomSave << endl;
		ofstream fich(nomSave.c_str());
		if (!fich.is_open())
			cout << "Impossible d'enregistrer ici, verifier le chemin du fichier" << endl;
		else
		{
			fich << "&&listemot&&" << endl;
			vector<Mot*>::iterator it; // Déclaration de l'itérateur
			for (it = listeMot_.begin(); it != listeMot_.end(); it++)
			{
				fich << (*it)->getText() << endl;
				fich << (*it)->getOccurence() << endl;
				fich << (*it)->getChoisi() << endl;
			}
			fich << "/&&listemot&&" << endl;
			fich << "&&settings&&" << endl;
			fich << nombreOccurenceChoisi_ << endl;
			fich << nombreAffiche_ << endl;
			fich << police_ << endl;
			fich << courbe_ << endl;
			fich << orientation_ << endl;
			fich << "/&&settings&&" << endl;
			cout << "Sauvegarde effectuée !" << endl;
			system("pause");

		}
	}
	else
	{
		cout << "Abandon" << endl;
	}
}


Diagramme Diagramme::charger() {

	Diagramme diag;
	char reponse;
	cout << "Attention, les donnees non enregistrées seront effacées" << endl;
	cout << "Souhaitez-vous poursuivre ? (o/n)" << endl;
	cin >> reponse;
	if ((reponse == 'o') || (reponse == 'O')) 
	
	{


	}

	string nomOpen = getOpenFileName("Nom du fichier à sauvegarder :", "Fichiers genmots (*.genmots )");

	if (nomOpen != "")
	{
		cout << "Nom du fichier chargé : " << nomOpen << endl;
		ifstream fich(nomOpen.c_str());
		if (!fich.is_open())
		{

			cout << "Erreur d'ouverture, verifier le chemin du fichier" << endl;
		}

		else
		{
			string ligne;
			do {
				getline(fich, ligne);
			} while (ligne != "&&listemot&&");

			do {
				getline(fich, ligne);
				Mot mot(ligne);
				getline(fich, ligne);
				mot.setOccurence(stoi(ligne));
				getline(fich, ligne);
				mot.setChoisi(ligne == "1");
				diag.ajouterMot(&mot);

			} while (ligne != "/&&listemot&&");

			do {
				getline(fich, ligne);

			} while (ligne != "&&settings&&");
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
			/*if (ligne != "/&&settings&&") {
				cerr << "sauvegarde endommagée, les donnees risquent d'être détériorées" << endl;
				
			}*/
			fich.close();
			return diag;

		}

	}

}

void Diagramme::exporter() {

}


void Diagramme::choixOrientation() {
	system("cls");
	cout << "Actuellement, le nuage affiche les mots avec une orientation maximale de +/- " << getOrientation() << " degres, quelle orientation souhaitez vous avoir ?" << endl;
	cin >> orientation_;
}

void Diagramme::choixNombre() {
	system("cls");
	cout << "Actuellement, le nuage affiche " << getNombre() << " mots, combien souhaitez vous en afficher ?" << endl;
	cin >> nombreAffiche_;
}

void Diagramme::choixPolice() {

}

void Diagramme::choixCourbe() {
	int courbe;
	system("cls");
	cout << "Actuellement, le nuage affiche le nuage autour d'une courbe : " << nomCourbe(getCourbe()) << endl << "Quelle courbe souhaitez-vous utiliser ?" << endl;
	for (int courbe = 0; courbe < NOMBRE_DE_COURBE ; courbe++) {
		cout << courbe + 1 << ") " << nomCourbe(courbe) << endl;
	}
	cin >> courbe;
	courbe_ = (Courbe)(courbe-1);
}


string nomCourbe(int idCourbe) {
	switch (idCourbe) {
	case 0:
		return "Cercle";
	case 1:
		return "Rectangle";
	default:
		return "Erreur de courbe";
	}
}