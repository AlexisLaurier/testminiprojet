#include <iostream>
#include <string>
#include "Mot.h"

using namespace std;

Mot::Mot() {
	text_ = new string;
	occurence_ = 1;
	choisi_ = true;
}


Mot::Mot(string& text) :text_(&text) {
	occurence_ = 1;
	choisi_ = true;
}

Mot::Mot(const Mot &mot) : text_(mot.getText()) {
	occurence_ = mot.getOccurence();
	choisi_ = mot.getChoisi();
}

Mot::~Mot() {
	delete text_;
}

