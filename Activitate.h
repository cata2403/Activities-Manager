#pragma once
#include <iostream>
#include <string>
using std::string;
using std::cout;

class Activitate
{
private:
	string  titlu;
	string descriere;
	string tip;
	int durata;

public:
	Activitate() = default;

	Activitate(const string& titlu, const string& descriere, const string& tip, const int durata) :
		titlu{ titlu }, descriere{ descriere }, tip{ tip }, durata{ durata } {};

	//Activitate(const Activitate& a) : titlu{ a.titlu }, descriere{ a.descriere }, tip{ a.tip }, durata{ a.durata } { cout << a.titlu<<" ";}; 

	const string& get_titlu() const noexcept;

	const string& get_descriere() const noexcept;

	const string& get_tip() const noexcept;

	int get_durata() const noexcept;

	const string str_activitate() const;
};