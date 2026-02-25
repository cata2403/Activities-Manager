#include "validator.h"
#include <stdexcept>

const char* Validator_Exception::what() const noexcept
{
	return msg.c_str();
}

bool Validator::verificare_string(const string& s) const
{
	for (auto i : s)
		if (!isalpha(i) && i != ' ')
			return false;
	if (s.at(0) == ' ' || s.at(s.size() - 1) == ' ')
		return false;
	return true;
}

bool Validator::verificare_durata(const int durata) const noexcept
{
	if (durata < 0)
		return false;
	return true;
}

void Validator::validare_activitate(const Activitate& activitate) const
{
	string eroare{ "" };
	if (!verificare_string(activitate.get_titlu()))
		eroare += "<Titlu introdus gresit>\n";
	if (!verificare_string(activitate.get_tip()))
		eroare += "<Tip introdus gresit>\n";
	if (!verificare_durata(activitate.get_durata()))
		eroare += "<Durata introdusa gresit>\n";
	if (eroare.size() > 0)
		throw Validator_Exception(eroare);
}