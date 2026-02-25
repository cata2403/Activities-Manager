#include "repo_activitati.h"
#include <stdexcept>


void Repo_Memorie::adaugareNoUnique(const Activitate& activitate) 
{
	elems.push_back(activitate);
}

void Repo_Memorie::adaugare(const Activitate& activitate)
{
	const string id_activitate{ activitate.get_titlu() };
	auto iter = find_if(elems.begin(), elems.end(), [&](const Activitate& a) noexcept {return a.get_titlu() == id_activitate; });
	if (iter != elems.end())
		throw Repo_Exception("<Activitatea este deja adaugata>");
	elems.push_back(activitate);
}

void Repo_Memorie::stergere(const string& titlu)
{
	auto iter = find_if(elems.begin(), elems.end(), [&](const Activitate& a) noexcept {return a.get_titlu() == titlu; });
	if (iter == elems.end())
		throw Repo_Exception("<Activitatea nu exista>");
	elems.erase(iter);
}

void Repo_Memorie::modificare(const Activitate& activitate)
{
	const string id_activitate{ activitate.get_titlu() };
	auto iter = find_if(elems.begin(), elems.end(), [&](const Activitate& a) noexcept {return a.get_titlu() == id_activitate; });
	if (iter == elems.end())
		throw Repo_Exception("<Activitatea nu exista>");
	elems.at(iter - elems.begin()) = activitate;
}

const Activitate& Repo_Memorie::cautare(const string& titlu) const
{
	auto iter = find_if(elems.begin(), elems.end(), [&](const Activitate& a) noexcept {return a.get_titlu() == titlu; });
	if (iter == elems.end())
		throw Repo_Exception("<Activitatea nu exista>");
	return elems.at(iter - elems.begin());
}

void Repo_Memorie::golire() noexcept
{
	elems.clear();
}

const vector<Activitate>& Repo_Memorie::get_all()const noexcept
{
	return elems;
}