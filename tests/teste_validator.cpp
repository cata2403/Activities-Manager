#include "teste_validator.h"
#include "validator.h"
#include <assert.h>
#include <stdexcept>
#include <iostream>


void TestValidator::test_validare_activitate()
{
	const Validator v;
	Activitate a{ " dvaiyw", "dwiua", "vdyua", 123 };
	try
	{
		v.validare_activitate(a);
		assert(false);
	}
	catch (const exception& error)
	{
		assert(!strcmp(error.what(), "<Titlu introdus gresit>\n"));
		assert(true);
	}
	a = { "dguawbi", "6kd;adj", "dbu;'ia", 45 };
	try
	{
		v.validare_activitate(a);
		assert(false);
	}
	catch (exception)
	{
		assert(true);
	}
	a = { "df g", "v v", "adgyua ", 63 };
	try
	{
		v.validare_activitate(a);
		assert(false);
	}
	catch (exception)
	{
		assert(true);
	}
	a = { "dwa", "dawd", "adgyua", -817 };
	try
	{
		v.validare_activitate(a);
		assert(false);
	}
	catch (exception)
	{
		assert(true);
	}
	a = { "t   t", "hduiwa du daiy", "gd n  gwa", 0 };
	try
	{
		v.validare_activitate(a);
		assert(true);
	}
	catch (const exception& e)
	{
		cout << e.what();
		assert(false);
	}
}

void TestValidator::test_all_validator()
{
	test_validare_activitate();
}