#pragma once
#include "Activitate.h"
#include <vector>
#include <stdexcept>

using std::vector;

class Repo_Exception :public std::exception
{
private:
	string msg;
public:
	Repo_Exception(const string& m) : msg{ m } {};
	const char* what() const noexcept override
	{
		return msg.c_str();
	}
};

class RepoActivitati
{
public:
	virtual void adaugare(const Activitate&) = 0;
	virtual void stergere(const string&) = 0;
	virtual void modificare(const Activitate&) = 0;
	virtual const Activitate& cautare(const string&) const = 0;
	virtual void golire() = 0;
	virtual const vector<Activitate>& get_all() const = 0;
	virtual ~RepoActivitati() = default;
};