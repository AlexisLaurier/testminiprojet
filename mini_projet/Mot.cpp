//Julian Romain et Laurier Alexis
#include <iostream>
#include <string>
#include "Mot.h"

using namespace std;

// Constructeur par défaut
Mot::Mot() {
	text_ = new string;
	occurence_ = 1;
	choisi_ = true;
}

// Constructeur prenant le texte du mot en entrée
Mot::Mot(string& text) :text_(&text) {
	occurence_ = 1;
	choisi_ = true;
}

// Constructeur de copie
Mot::Mot(const Mot &mot) : text_(mot.getText()) {
	occurence_ = mot.getOccurence();
	choisi_ = mot.getChoisi();
}

// Destructeur
Mot::~Mot() {
	delete text_;
}

