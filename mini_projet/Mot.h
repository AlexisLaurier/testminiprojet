#ifndef MOT_H
#define MOT_H

#include <string>

class Mot;
// Realise par Romain JULIAN
class Mot {
	std::string text_;
	int occurence_;
	bool choisi_;
	
public:
	Mot(std::string text);
	void apparu() { occurence_ += 1;}  // incremente le nombre d'occurence
	bool getChoisi() const { return choisi_; }
	std::string getText() const { return text_; }
	int getOccurence() const { return occurence_; }
	void setOccurence(int occurence) { occurence_ = occurence; }
	void setChoisi(bool choix) { choisi_ = choix; }

};



#endif