#pragma once
#include "repository.h"
#include "Activitate.h"
#include <vector>
#include <string>
using std::string;
using std::vector;

class Repo_Memorie : public RepoActivitati
{
private:
	vector<Activitate> elems;
public:

	void adaugareNoUnique(const Activitate& activitate);

	void adaugare(const Activitate& activitate) override;

	void stergere(const string& titlu) override;

	void golire() noexcept override;

	void modificare(const Activitate& activitate) override;

	const Activitate& cautare(const string& titlu) const override;

	const vector<Activitate>& get_all()const noexcept override;
};