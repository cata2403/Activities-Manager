#include "utilitati.h" 
#include <algorithm>
#include <random>
#include <chrono>

const string Utils::rand_cuvant()
{
	string abc{ "qwertyuioplkjhgfdsazxcvbnm" };
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(abc.begin(), abc.end(), std::default_random_engine((unsigned)seed));
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_int_distribution<> dist(0, (int)abc.size() - 1);
	int nr1 = dist(mt), nr2 = dist(mt);
	if (nr2 < nr1)std::swap(nr1, nr2);
	return abc.substr(nr1, nr2 - nr1 + 1);
}

int Utils::rand_numar()
{
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_int_distribution<> dist(0, 1000);
	return dist(mt);
}