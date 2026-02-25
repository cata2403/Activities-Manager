#pragma once
#include <string>
#include "Activitate.h" 
using namespace std;

class Validator_Exception :public exception
{
private:
	string msg;
public:
	Validator_Exception(const string& m) : msg{ m } {};
	const char* what() const noexcept override;
};

class Validator
{
public:
	bool verificare_string(const string&) const;
	bool verificare_durata(const int durata) const noexcept;
	void validare_activitate(const Activitate& activitate) const;
};