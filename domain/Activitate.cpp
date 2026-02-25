#include "Activitate.h"
#include <string>

using std::string;
using std::to_string;

const string& Activitate::get_titlu() const noexcept
{
	return titlu;
}

const string& Activitate::get_descriere() const noexcept
{
	return descriere;
}

const string& Activitate::get_tip() const noexcept
{
	return tip;
}

int Activitate::get_durata() const noexcept
{
	return durata;
}


const string Activitate::str_activitate() const
{
	string str{ "" };
	str += "Titlu: ";
	str += titlu;
	str += " | Tip: ";
	str += tip;
	str += " | Durata: ";
	str += to_string(durata);
	str += "\nDescriere: ";
	str += descriere;
	return str;
}