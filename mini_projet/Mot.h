#ifndef __MOT__
#define __MOT__

#include <string>

class Mot;
// Realise par Romain JULIAN
class Mot {
	std::string * text_;
	int occurence_;
	bool choisi_;
	
public:
	Mot();
	Mot(std::string &text);
	Mot(const Mot &mot);
	~Mot();
	void apparu() { occurence_ += 1;}  // incremente le nombre d'occurence
	bool getChoisi() const { return choisi_; }
	std::string* getText() const { return text_; }
	int getOccurence() const { return occurence_; }
	void setOccurence(int occurence) { occurence_ = occurence; }
	void setChoisi(bool choix) { choisi_ = choix; }
	void setText(std::string texte) { text_ = new std::string(texte); }
	void changeChoisi() { choisi_ = !choisi_; }

};



#endif