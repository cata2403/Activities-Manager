#include "Activitate.h"
#include "teste_domain.h"
#include <assert.h>

void TestDomain::test_getter()
{
	Activitate b;
	Activitate a{ "scris", "nu vreau", "asa", 123 };
	assert(a.get_titlu() == "scris");
	assert(a.get_descriere() == "nu vreau");
	assert(a.get_tip() == "asa");
	assert(a.get_durata() == 123);
	a = Activitate("", "", "", -1);
	assert(a.get_titlu() == "");
	assert(a.get_descriere() == "");
	assert(a.get_tip() == "");
	assert(a.get_durata() == -1);
}

void TestDomain::test_str_activitate()
{
	const Activitate a{ "scris", "nu vreau", "asa", 123 };
	const string str = a.str_activitate();
	assert(str == "Titlu: scris | Tip: asa | Durata: 123\nDescriere: nu vreau");
}

void TestDomain::test_all_domain()
{
	test_getter();
	test_str_activitate();
}