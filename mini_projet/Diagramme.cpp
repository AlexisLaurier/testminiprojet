#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <fstream>
#include <ctype.h>
#include <sstream>
#include <algorithm>
#include <time.h>

#include "Menu.h"
#include "Diagramme.h"
#include "filedialog.h"
#include "CImg.h"

#pragma warning(disable:4996)

using namespace std;
using namespace cimg_library;

bool comparerMot(const Mot *elem1, const Mot *elem2)
{
	return elem1->getOccurence() > elem2->getOccurence();
}

Diagramme::Diagramme() {
	listeMot_.clear();
	nombreAffiche_ = 20;  //20 mots par défaut
	police_ = "testPolice"; // Police par défaut à définir
	courbe_ = cercle; 
	orientation_ = 45.0; // Inclinaison par défaut de +/- 45°
	menu_ = new MenuDiagramme(*this);
	origine_ = new MenuPrincipal(*this);
	CImg<unsigned char> grid(600, 600, 1, 3, 255);
	scene_ = grid;
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
	CImg<unsigned char> grid(600, 600, 1, 3, 255);
	scene_ = grid;
}


void Diagramme::creerListe() 
{
	char reponse;
	cout << "Attention, les donnees non enregistrees seront effacees" << endl;
	cout << "Souhaitez-vous poursuivre ? (o/n)" << endl;
	cin >> reponse;
	if ((reponse == 'n') || (reponse == 'N'))
	{
		return;
	}

	string nomOpen = getOpenFileName("Nom du fichier a charger :", "Fichiers txt (*.txt )");

	if (nomOpen != "")
	{
		cout << "Nom du fichier charge : " << nomOpen << endl;
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
				//recherche des extrémaux en nombre d'occurence
				int min = 1;
				int max = 1;
				int value = 0;
				vector<Mot*>::iterator it; // Déclaration de l'itérateur
				for (it = listeMot_.begin(); it != listeMot_.end(); it++)
				{
					value = (*it)->getOccurence();
					if (value > max) { max = value; }
					if (value < min) { min = value; }

				}

				if (max != 0) {
					for (it = listeMot_.begin(); it != listeMot_.end(); it++)
					{
						double occurence;
						occurence = (*it)->getOccurence();
						occurence = (occurence - min) / (max - min);
						(*it)->setOccurenceNormalisee(occurence);

					}

				}
		}
	}
}

void Diagramme::ajouterMot(Mot * mot) {

	listeMot_.push_back(mot);

}

void Diagramme::choixMot() {
	system("cls");
	int page = 0; int i = 0;
	vector<Mot*>::iterator it; 
	string erreur ="";
	string choix;
	while(choix != "exit") {
		cout << left << setw(14) << "N°ligne" << setw(25) << "Mot : " << setw(22) << "Nombre d'apparition" << setw(14) << "L'afficher ?" << endl;
		for (it = listeMot_.begin() + (19 * page); (it != listeMot_.end()) && i<19 ; it++)
		{
			string affiche;
			if ((*it)->getChoisi()) { affiche = "oui"; }
			else { affiche = "non"; };
			cout << left << setw(14) << i+1 << setw(25) << *(*it)->getText() << setw(22) << (*it)->getOccurence() << setw(14) << affiche << endl;
			i += 1;
		}
		i = 0;
		cout << "Affichage de la page " << page + 1 << endl;
		cout << "Changer statut mot : numero ligne ; Changer numero page : p+, p-, px ;retourner menu principal : exit" << endl;
		cout << endl << erreur;
		cin >> choix;
		if (isdigit(choix[0]))
		{
			int indice = stoi(choix);
			if (indice + 19 * page <= listeMot_.size()) {
				(listeMot_[(indice - 1) + 19*page])->changeChoisi();
				erreur = "";
			}
			else {
				erreur = "Erreur d'indice";
			}
			
		}
		else {
			if(choix[0] == 'p')
			{ 
				switch (choix[1])
				{
				case '+':
					if (listeMot_.size() > (page+1) * 19) {
						page = page + 1; 
						erreur = "";
					}
					else {
						erreur = "Plus d'autres mots";
					}
					break;
				case '-':
					if (page >= 1)
					{
						page = page - 1;
						erreur = "";
					}
					else
						erreur= "Vous etes deja a la premiere page !";
				
					break;
				default :
				{
					int pageCible = stoi(choix.erase(0,1));
					if(listeMot_.size() > 19*(pageCible-1))
					{
						page = pageCible-1;
						erreur = "";
					}
					else {
						erreur = "choix incorrect";
					}

				}

			}
			
			}
			
			

		}
		system("cls");
	}

}

bool comparerMotAleatoire(const Mot *elem1, const Mot *elem2)
{
	srand(time(NULL));
	double rnd = rand() % 100;
	rnd = rnd / 10;
	return elem1->getOccurenceNormalisee() > elem2->getOccurenceNormalisee()*rnd;
}

void Diagramme::afficher(MenuPrincipal &origine, bool reload) {
	// Création et affichage du nuage à ajouter
	// Usefull colors
	vector<Mot*> listeMotAleatoire = listeMot_;
	sort(listeMotAleatoire.begin(), listeMotAleatoire.end(), comparerMotAleatoire);
	unsigned char grid_color[3] = { 0,0,255 };

	// Declare an image to draw the grid
	CImg<unsigned char> grid(600, 600, 1, 3, 255);

	// Declare a display to draw the scene
	CImgDisplay disp(grid, "Generateur de mot", 0, false, false);

	// Center the window on the screen
	disp.move((CImgDisplay::screen_width() - disp.width()) / 2,
		(CImgDisplay::screen_height() - disp.height()) / 2);



	// Main loop, exit if the display window is closed or if ESC or Q key is hit


		// Display the scene
		// Declare an image to display the scene
		scene_ = grid;
		Point point{ 300,300,0 };
		srand(time(NULL));
		int nombreMotAffiche = 0;
		for (vector<Mot*>::iterator it = listeMotAleatoire.begin(); it != listeMotAleatoire.end() && nombreMotAffiche<nombreAffiche_; it++) {
			if ((*it)->getChoisi()) {
				unsigned char color[] = { rand() % 256, rand() % 256,rand() % 256 };

				bool utilise = false;
				string text = *(*it)->getText();

				int hauteur = 15 + 40 * (*it)->getOccurenceNormalisee();
				int longueur = text.size()*hauteur;

				for (int i = point.x; i < point.x + longueur + 10;i++) {
					for (int j = point.y;j < point.y + hauteur + 10;j++) {

						int r = (int)scene_(i, j, 0, 0);
						int g = (int)scene_(i, j, 0, 1);
						int b = (int)scene_(i, j, 0, 2);
						if (r + g + b != 765) {
							utilise = true;
						}


					}
				}
				if (!utilise) {
					scene_.draw_text(point.x, point.y, text.c_str(), color, 0, 1, hauteur);
					nombreMotAffiche++;
				}
				else {
					it--;
				}
				point = prochainPoint(cercle, point);
			}
		}
		


		
		// Usefull variables

		scene_.display(disp);

		disp.wait();

		// Handle window resize
		if (disp.is_resized()) disp.resize();







	if (!reload) {
		origine_ = &origine;
		menu_->setDiagramme(*this);
		menu_->getDiagramme()->setOrigine(&origine);
		menu_->executer();

		
	}
	
}

//http://stackoverflow.com/questions/20446201/how-to-check-if-string-ends-with-txt
bool has_suffix(const std::string &str)
{
	string suffix = "genmots"; 
	return str.size() >= suffix.size() &&
		str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

void Diagramme::sauvegarde() {
	cout << "Merci de choisir dans quel fichier effectuer la sauvegarde" << endl;
	string nomSave = getSaveFileName("Nom du fichier a sauvegarder :", "Fichiers genmots (*.genmots )");
	if (!has_suffix(nomSave))
		nomSave += ".genmots";
	if (nomSave != "")
	{
		cout << "Nom du fichier sauvegarde : " << nomSave << endl;
		ofstream fich(nomSave.c_str());
		if (!fich.is_open())
			cout << "Impossible d'enregistrer ici, verifier le chemin du fichier" << endl;
		else
		{
			fich << "&&listemot&&" << endl;
			vector<Mot*>::iterator it; // Déclaration de l'itérateur
			for (it = listeMot_.begin(); it != listeMot_.end(); it++)
			{
				fich << *(*it)->getText() << endl;
				fich << (*it)->getOccurence() << endl;
				fich << (*it)->getChoisi() << endl;
			}
			fich << "/listemot&&" << endl;
			fich << "&&settings&&" << endl;
			fich << nombreOccurenceChoisi_ << endl;
			fich << nombreAffiche_ << endl;
			fich << police_ << endl;
			fich << courbe_ << endl;
			fich << orientation_ << endl;
			fich << "/settings&&" << endl;
			cout << "Sauvegarde effectuee !" << endl;
			system("pause");

		}
	}
	else
	{
		cout << "Abandon" << endl;
	}
}


void Diagramme::charger() {

	Diagramme diag;
	char reponse;
	cout << "Attention, les donnees non enregistrees seront effacees" << endl;
	cout << "Souhaitez-vous poursuivre ? (o/n)" << endl;
	cin >> reponse;
	if ((reponse == 'N') || (reponse == 'n')) 
	{
		exit;
	}

	string nomOpen = getOpenFileName("Nom du fichier a sauvegarder :", "Fichiers genmots (*.genmots )");

	if (nomOpen != "")
	{
		cout << "Nom du fichier charge : " << nomOpen << endl;
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
			getline(fich, ligne);
			do {
				Mot *mot = new Mot;
				mot->setText(ligne);
				getline(fich, ligne);
				mot->setOccurence(stoi(ligne));
				getline(fich, ligne);
				mot->setChoisi(ligne == "1");
				diag.ajouterMot(mot);
				getline(fich, ligne);

			} while (ligne != "/listemot&&");

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
			fich.close();
			if (ligne != "/settings&&") {
				cerr << "sauvegarde endommagee, les donnees n'ont pas été importees" << endl;
				system("pause");
				exit;

			}
	
			*this = diag;
			//recherche des extrémaux en nombre d'occurence
			int min = 0;
			int max = 0;
			int value = 0;
			vector<Mot*>::iterator it; // Déclaration de l'itérateur
			for (it = listeMot_.begin(); it != listeMot_.end(); it++)
			{
				value = (*it)->getOccurence();
				if (value > max) { max = value; }
				if (value < min) { min = value; }

			}

			if (max != 0) {
				for (it = listeMot_.begin(); it != listeMot_.end(); it++)
				{
					double occurence;
					occurence = (*it)->getOccurenceNormalisee();
					occurence = (occurence - min) / (max - min);
					(*it)->setOccurenceNormalisee(occurence);

				}

			}
			cout << "Chargement effectuee !" << endl;
			system("pause");
			return;

		}

	}

}

void Diagramme::exporter() {
	string nomSave = getSaveFileName("Nom du fichier a sauvegarder :", "Fichiers image (*.ppm )");
	scene_.save(nomSave.c_str());

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

Point Diagramme::prochainPoint(Courbe courbe, Point pointActuelle) {
	int t = pointActuelle.posCourbe;
	Point prochainPoint = { 0,0,t + 1 };
	switch (courbe) {
	case cercle:
		prochainPoint.x = 300+10*t*sin(36000*t);
		prochainPoint.y = 300+10*t*cos(36000*t);
		break;
	case rectangle:
		break;
	}
	return prochainPoint;

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



